/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:50:50 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/06 01:49:53 by isastre-         ###   ########.fr       */
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
		return (1);

	
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
