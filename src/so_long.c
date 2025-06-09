/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:50:50 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/09 19:36:17 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_file_is_dot_ber(char *file);

int main(int argc, char *argv[])
{
	t_map_data	*map = ft_calloc(1, sizeof(t_map_data));
	
	// check map arg exists
	if (argc != 2)
		return (1);
	
	// check if .ber
	if (!ft_file_is_dot_ber(argv[1]))
		return (1);
	
	// count map lines
	map->height = ft_get_map_height(argv[1]);
	if (map->height < 3)
		return (1);
	
	// save map lines
	map->content = ft_save_map_content(argv[1], map->height);
	if (map->content == NULL)
		return (1);
	
	// check if map width is always the same
	map->width = ft_validate_and_get_map_width(map->content, map->height);
	if (map->width < 3)
		return (1);
	
	// validate map content
	if (ft_validate_components(map) || map->exit != 1
		|| map->player != 1 || map->collectionable < 1)
		return (1);

	printf("width: %d height: %d\n", map->width, map->height);
	printf("exit: %d player: %d collectionables: %d\n", map->exit, map->player, map->collectionable);

	if (ft_validate_outer_walls(map))
	{
		printf("Falta algun muro rodeando el mapa\n");
		return (1);
	}

	t_map_data *map_copy = malloc(sizeof(t_map_data)); // TODO check error
	ft_memcpy(map_copy, map, sizeof(t_map_data));
	
	ft_flood_fill(map_copy, map_copy->player_row, map_copy->player_col);
	if (map_copy->exit != 0 || map_copy->player != 0 || map_copy->collectionable != 0)
	{
		printf("error despues de flood fill - remains exit: %d player: %d collectionables: %d\n", map_copy->exit, map_copy->player, map_copy->collectionable);
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
