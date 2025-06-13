/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:12:25 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/13 02:26:22 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_open_xpms(t_game_data *game)
{
	game->xmp_exit = mlx_xpm_file_to_image(game->mlx_instance, SPRITE_EXIT,
			&game->sprite_side, &game->sprite_side);
	game->xmp_collectible = mlx_xpm_file_to_image(game->mlx_instance,
			SPRITE_COLLECTIBLE, &game->sprite_side, &game->sprite_side);
	game->xmp_player = mlx_xpm_file_to_image(game->mlx_instance, SPRITE_PLAYER,
			&game->sprite_side, &game->sprite_side);
	game->xmp_wall = mlx_xpm_file_to_image(game->mlx_instance, SPRITE_WALL,
			&game->sprite_side, &game->sprite_side);
	game->xmp_floor = mlx_xpm_file_to_image(game->mlx_instance, SPRITE_FLOOR,
			&game->sprite_side, &game->sprite_side);
	return (game->xmp_exit != NULL && game->xmp_collectible != NULL
		&& game->xmp_player != NULL && game->xmp_wall != NULL
		&& game->xmp_floor != NULL);
}

void	ft_close_xpms(t_game_data *game)
{
	if (game->xmp_collectible)
		mlx_destroy_image(game->mlx_instance, game->xmp_collectible);
	if(game->xmp_exit)
		mlx_destroy_image(game->mlx_instance, game->xmp_exit);
	if(game->xmp_floor)
		mlx_destroy_image(game->mlx_instance, game->xmp_floor);
	if(game->xmp_player)
		mlx_destroy_image(game->mlx_instance, game->xmp_player);
	if(game->xmp_wall)
		mlx_destroy_image(game->mlx_instance, game->xmp_wall);
}

void	ft_put_sprite(t_game_data *game, void *sprite, int y, int x)
{
	mlx_put_image_to_window(game->mlx_instance, game->mlx_window, sprite,
		x * SPRITE_SIDE_PIXELS, y * SPRITE_SIDE_PIXELS);
}
