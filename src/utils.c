/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:51:14 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/13 22:30:37 by isastre-         ###   ########.fr       */
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
	ft_printf("Error\n");
	ft_printf("%s\n", error_msg);
}

void	ft_init_game_struct(t_game_data *game, t_map_data **map)
{
	game->map = *map;
	game->mlx_window = NULL;
	game->movs = 0;
	game->sprite_side = SPRITE_SIDE_PIXELS;
	game->xpm_collectible = NULL;
	game->xpm_exit = NULL;
	game->xpm_floor = NULL;
	game->xpm_player = NULL;
	game->xpm_wall = NULL;
	game->mlx_instance = mlx_init();
	if (game->mlx_instance == NULL)
		ft_end_game(game);
}

int	ft_end_game(t_game_data *mlx)
{
	ft_close_xpms(mlx);
	if (mlx->mlx_window)
		mlx_destroy_window(mlx->mlx_instance, mlx->mlx_window);
	if (mlx->mlx_instance)
	{
		mlx_destroy_display(mlx->mlx_instance);
		free(mlx->mlx_instance);
	}
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
