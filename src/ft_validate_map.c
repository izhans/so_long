/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:35:08 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/12 22:54:40 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_validate_content(t_map_data *map);
static int	ft_valid_content(char c);
static void	ft_set_player_position(t_map_data *map, int row, int col);
static int	ft_validate_outer_walls(t_map_data *map);

/**
 * @brief validates map chars, map is surrounded by walls 
 * 			and map is possible to win
 * @return 0 if valid, 1 if invalid
 */
int	ft_validate_map(t_map_data *map)
{
	if (ft_validate_content(map) || map->exit != 1
		|| map->player != 1 || map->collectionable < 1)
		return (ft_print_error(ERROR_MAP_CONTENT), 1);
	if (ft_validate_outer_walls(map))
		return (ft_print_error(ERROR_MAP_NOT_SURROUNDED_BY_WALLS), 1);
	if (!ft_validate_flood_fill(map))
		return (ft_print_error(ERROR_MAP_IMPOSSIBLE_WIN), 1);
	map->content[map->player_row][map->player_col] = MAP_EMPTY;
	return (0);
}

static int	ft_validate_content(t_map_data *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->content[i])
	{
		j = 0;
		while (j < map->width)
		{
			if (!ft_valid_content(map->content[i][j]))
				return (1);
			if (map->content[i][j] == MAP_EXIT)
				map->exit++;
			else if (map->content[i][j] == MAP_PLAYER)
			{
				map->player++;
				ft_set_player_position(map, i, j);
			}
			else if (map->content[i][j] == MAP_COLLECTIBLE)
				map->collectionable++;
			j++;
		}
		i++;
	}
	return (0);
}

static int	ft_valid_content(char c)
{
	return (ft_strchr(MAP_COMPONENTS, c) != NULL);
}

static void	ft_set_player_position(t_map_data *map, int row, int col)
{
	map->player_row = row;
	map->player_col = col;
}

static int	ft_validate_outer_walls(t_map_data *map)
{
	int	i;
	int	last_row;
	int	last_col;

	i = 0;
	last_row = map->height -1;
	while (i < map->width)
	{
		if (map->content[0][i] != MAP_WALL
			|| map->content[last_row][i] != MAP_WALL)
			return (1);
		i++;
	}
	i = 0;
	last_col = map->width -1;
	while (i < map->height)
	{
		if (map->content[i][0] != MAP_WALL
			|| map->content[i][last_col] != MAP_WALL)
			return (1);
		i++;
	}
	return (0);
}
