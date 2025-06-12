/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:50:50 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/13 00:41:58 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ft_handle_key(int keysym, t_game_data *mlx);
void	ft_paint_map(t_game_data *game);
void	ft_move(t_map_data *map, int row, int col, t_game_data *game);

int main(int argc, char *argv[])
{
	t_map_data	*map;
	t_game_data	mlx;
	
	// check map arg exists + check if .ber
	if (argc != 2 || !ft_file_is_dot_ber(argv[1]))
		return (1);
	
	map = ft_calloc(1, sizeof(t_map_data)); // TODO check errors or pass to non dinamic memory
	if (ft_init_map(map, argv[1]) || ft_validate_map(map))
		return (ft_free_map_struct(map), 1);
	printf("mapa bien\n");

	// TODO check mlx_data creation errors
	mlx.mlx_instance = mlx_init();
	mlx.mlx_window = mlx_new_window(mlx.mlx_instance, map->height * SPRITE_SIDE_PIXELS,
		map->width * SPRITE_SIDE_PIXELS, "so_long");
	
	mlx.map = map;
	mlx.movs = 0;
	if (!ft_open_xpms(&mlx))
		return (ft_print_error("Error al abrir algun xmp"), 1);

	ft_paint_map(&mlx);

	mlx_key_hook(mlx.mlx_window, ft_handle_key, &mlx);
	mlx_hook(mlx.mlx_window, MLX_CLOSE_WINDOW_BUTTON, NoEventMask, ft_end_game, &mlx);
	
	mlx_loop(mlx.mlx_instance); // ? si no hay ventana se acaba el loop ?
	
	// free map + map data + destroy images
	ft_free_map_struct(map); // this is never actually executed
	return 0;
}

int ft_handle_key(int keysym, t_game_data *mlx)
{
	if (keysym == XK_Escape)
		ft_end_game(mlx);
	else if (keysym == XK_Down)
		ft_move(mlx->map, 0, 1, mlx);
	else if (keysym == XK_Up)
		ft_move(mlx->map, 0, -1, mlx);
	else if (keysym == XK_Left)
		ft_move(mlx->map, -1, 0, mlx);
	else if (keysym == XK_Right)
		ft_move(mlx->map, 1, 0, mlx);
	ft_paint_map(mlx);
	printf("movs %d\n", mlx->movs);
	return (0);
}

void	ft_move(t_map_data *map, int row, int col, t_game_data *game)
{
	char	tile;
	if (map->content[map->player_row + row][map->player_col + col] == MAP_WALL)
		return ;
	map->player_row += row; 
	map->player_col += col;
	tile = map->content[map->player_row][map->player_col];
	if (tile == MAP_COLLECTIBLE)
	{
		map->content[map->player_row][map->player_col] = MAP_EMPTY;
		map->collectionable--;
	}
	else if (tile == MAP_EXIT && map->collectionable == 0)
	{
		ft_end_game(game);
	}
	game->movs++;
}

void	ft_paint_map(t_game_data *game)
{
	printf("ft_paint_map\n");
	printf("player i:%d j:%d\n", game->map->player_row, game->map->player_col);
	int		i;
	int		j;
	char	**map;
	
	i = 0;
	map = game->map->content;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (i == game->map->player_row && j == game->map->player_col)
				ft_put_sprite(game, game->xmp_player, i, j);
			else if (map[i][j] == MAP_EXIT)
				ft_put_sprite(game, game->xmp_exit, i, j);
			else if (map[i][j] == MAP_WALL)
			ft_put_sprite(game, game->xmp_wall, i, j);
			else if (map[i][j] == MAP_EMPTY)
				ft_put_sprite(game, game->xmp_floor, i, j);
			else if (map[i][j] == MAP_COLLECTIBLE)
				ft_put_sprite(game, game->xmp_collectible, i, j);
			j++;
		}
		i++;
	}
}
