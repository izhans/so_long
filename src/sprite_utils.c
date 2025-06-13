/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:12:25 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/13 05:09:20 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_open_xpms(t_game_data *game)
{
	game->xpm_exit = mlx_xpm_file_to_image(game->mlx_instance, SPRITE_EXIT,
			&game->sprite_side, &game->sprite_side);
	game->xpm_collectible = mlx_xpm_file_to_image(game->mlx_instance,
			SPRITE_COLLECTIBLE, &game->sprite_side, &game->sprite_side);
	game->xpm_player = mlx_xpm_file_to_image(game->mlx_instance, SPRITE_PLAYER,
			&game->sprite_side, &game->sprite_side);
	game->xpm_wall = mlx_xpm_file_to_image(game->mlx_instance, SPRITE_WALL,
			&game->sprite_side, &game->sprite_side);
	game->xpm_floor = mlx_xpm_file_to_image(game->mlx_instance, SPRITE_FLOOR,
			&game->sprite_side, &game->sprite_side);
	return (game->xpm_exit != NULL && game->xpm_collectible != NULL
		&& game->xpm_player != NULL && game->xpm_wall != NULL
		&& game->xpm_floor != NULL);
}

void	ft_close_xpms(t_game_data *game)
{
	if (game->xpm_collectible)
		mlx_destroy_image(game->mlx_instance, game->xpm_collectible);
	if (game->xpm_exit)
		mlx_destroy_image(game->mlx_instance, game->xpm_exit);
	if (game->xpm_floor)
		mlx_destroy_image(game->mlx_instance, game->xpm_floor);
	if (game->xpm_player)
		mlx_destroy_image(game->mlx_instance, game->xpm_player);
	if (game->xpm_wall)
		mlx_destroy_image(game->mlx_instance, game->xpm_wall);
}

void	ft_put_sprite(t_game_data *game, void *sprite, int y, int x)
{
	mlx_put_image_to_window(game->mlx_instance, game->mlx_window, sprite,
		x * SPRITE_SIDE_PIXELS, y * SPRITE_SIDE_PIXELS);
}
