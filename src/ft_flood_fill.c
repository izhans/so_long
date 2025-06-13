/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:16:34 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/13 21:54:40 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_make_map_copy(t_map_data	*map, t_map_data *map_copy);
static void	ft_flood_fill(t_map_data *map, int row, int col);

/**
 * @brief creates a copy of the map, runs flood_fill 
 * 		and checks if the map can be won
 * @return 1 if map is valid, 0 if invalid or error
 */
int	ft_validate_flood_fill(t_map_data *map)
{
	t_map_data	map_copy;

	if (ft_make_map_copy(map, &map_copy))
		return (0);
	ft_flood_fill(&map_copy, map->player_row, map->player_col);
	ft_free_str_array(map_copy.content);
	return (map_copy.exit == 0 && map_copy.player == 0
		&& map_copy.collectible == 0);
}

/**
 * @return 0 if the copy is made, 1 in case of error
 */
static int	ft_make_map_copy(t_map_data	*map, t_map_data *map_copy)
{
	int	i;

	map_copy->exit = map->exit;
	map_copy->player = map->player;
	map_copy->collectible = map->collectible;
	map_copy->height = map->height;
	map_copy->width = map->width;
	i = 0;
	map_copy->content = malloc((map->height + 1) * sizeof(char *));
	if (map_copy->content == NULL)
		return (ft_print_error(ERROR_MALLOC), 1);
	while (i < map->height)
	{
		map_copy->content[i] = ft_strdup(map->content[i]);
		if (map_copy->content[i] == NULL)
		{
			ft_free_map_struct(map_copy);
			return (ft_print_error(ERROR_MALLOC), 1);
		}
		i++;
	}
	map_copy->content[i] = NULL;
	return (0);
}

/**
 * @brief recursive function that fills an empty space surrounded by walls
 * 	the function calls itself moving up, right, down and left
 * 	when an special item [EPC] is found is marked
 * 	the visited tile is marked as visited
 */
static void	ft_flood_fill(t_map_data *map, int row, int col)
{
	if (row < 0 || col < 0 || row >= map->height || col >= map->width
		|| map->content[row][col] == MAP_WALL
		|| map->content[row][col] == MAP_VISITED)
		return ;
	if (map->content[row][col] == MAP_COLLECTIBLE)
		map->collectible--;
	if (map->content[row][col] == MAP_EXIT)
		map->exit--;
	if (map->content[row][col] == MAP_PLAYER)
		map->player--;
	map->content[row][col] = MAP_VISITED;
	ft_flood_fill(map, row -1, col);
	ft_flood_fill(map, row, col +1);
	ft_flood_fill(map, row +1, col);
	ft_flood_fill(map, row, col -1);
}
