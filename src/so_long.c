/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:50:50 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/10 10:56:41 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_file_is_dot_ber(char *file);
int	ft_init_map(t_map_data	*map, char *map_file);
void ft_print_error(char *error_msg);

int main(int argc, char *argv[])
{
	t_map_data	*map = ft_calloc(1, sizeof(t_map_data));
	
	// check map arg exists + check if .ber
	if (argc != 2 || !ft_file_is_dot_ber(argv[1]))
		return (1);
	
	if (ft_init_map(map, argv[1]))
	{
		ft_free_map_struct(map);
		return (1);
	}
	printf("mapa bien\n");

	// free map + map data
	return 0;
}

int	ft_file_is_dot_ber(char *file)
{
	int	len;

	len = ft_strlen(file);
	return (len > 4 && ft_strncmp(file + (len -4), ".ber", 4) == 0);
}

int	ft_init_map(t_map_data	*map, char *map_file)
{
	t_map_data	*map_copy;

	// count map lines
	map->height = ft_get_map_height(map_file);
	if (map->height < 3)
		return (ft_print_error("Map must have at least 3 lines"), 1);
	
	// save map lines
	map->content = ft_save_map_content(map_file, map->height);
	if (map->content == NULL)
		return (ft_print_error("Error saving map"), 1);
	
	// check if map width is always the same
	map->width = ft_validate_and_get_map_width(map->content, map->height);
	if (map->width < 3)
		return (ft_print_error("Map must be rectangular and at least have 3 columns"), 1);
	
	// validate map content
	if (ft_validate_components(map) || map->exit != 1
		|| map->player != 1 || map->collectionable < 1)
		return (ft_print_error("Invalid map components (accepts 01PEC): there must be 1 player, 1 exit and at least 1 collectible"), 1);

	printf("width: %d height: %d\n", map->width, map->height);
	printf("exit: %d player: %d collectionables: %d\n", map->exit, map->player, map->collectionable);

	if (ft_validate_outer_walls(map))
		return (ft_print_error("Invalid map: missing surrounding walls"), 1);
	
	map_copy = malloc(sizeof(t_map_data));
	if (map_copy == NULL)
		return (ft_print_error("Internal error checking map"), 1);
	ft_memcpy(map_copy, map, sizeof(t_map_data));
	
	ft_flood_fill(map_copy, map_copy->player_row, map_copy->player_col);
	if (map_copy->exit != 0 || map_copy->player != 0 || map_copy->collectionable != 0)
	{
		printf("error despues de flood fill - remains exit: %d player: %d collectionables: %d\n", map_copy->exit, map_copy->player, map_copy->collectionable);
		ft_free_map_struct(map_copy);
		return (ft_print_error("Inaccesible exit or collectibles"), 1);
	}
	return (ft_free_map_struct(map_copy), 0);
}

void ft_print_error(char *error_msg)
{
	printf("Error\n");
	printf("%s\n", error_msg);
}
