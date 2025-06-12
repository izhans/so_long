/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:16:34 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/12 23:10:01 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_flood_fill(t_map_data *map, int row, int col);

/**
 * @brief creates a copy of the map, runs flood_fill 
 * 		and checks if the map can be won
 * @return 1 if map is valid, 0 if invalid
 */
int	ft_validate_flood_fill(t_map_data *map)
{
	t_map_data	map_copy;

	ft_make_map_copy(map, &map_copy);
	ft_flood_fill(&map_copy, map->player_row, map->player_col);
	ft_free_str_array(map_copy.content);
	return (map_copy.exit == 0 && map_copy.player == 0
		&& map_copy.collectionable == 0);
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
		map->collectionable--;
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
