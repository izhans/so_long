/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:51:14 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/13 01:27:31 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	ft_file_is_dot_ber(char *file)
{
	int	len;

	len = ft_strlen(file);
	return (len > 4 && ft_strncmp(file + (len -4), ".ber", 4) == 0);
}

void	ft_print_error(char *error_msg)
{
	printf("Error\n");
	printf("%s\n", error_msg);
}

void	ft_make_map_copy(t_map_data	*map, t_map_data *map_copy)
{
	int	i;

	map_copy->exit = map->exit;
	map_copy->player = map->player;
	map_copy->collectionable = map->collectionable;
	map_copy->height = map->height;
	map_copy->width = map->width;

	i = 0;
	map_copy->content = malloc((map->height + 1) * sizeof(char *)); // TODO error
	while (i < map->height)
	{
		map_copy->content[i] = ft_strdup(map->content[i]); // TODO error
		i++;
	}
	map_copy->content[i] = NULL;
}

int	ft_end_game(t_game_data *mlx)
{
	ft_close_xpms(mlx);
	mlx_destroy_window(mlx->mlx_instance, mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_instance);
	free(mlx->mlx_instance);
	ft_free_map_struct(mlx->map);
	exit(0);
	return (0);
}

void	ft_free_map_struct(t_map_data *map)
{
	if (map == NULL)
		return ;
	ft_free_str_array(map->content);
	free(map);
}
