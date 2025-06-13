/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:50:50 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/13 21:54:40 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_handle_max_map_size(t_game_data *game);
int		ft_handle_key(int keysym, t_game_data *game);
void	ft_paint_map(t_game_data *game);
void	ft_move(t_map_data *map, int row, int col, t_game_data *game);

int	main(int argc, char *argv[])
{
	t_map_data	*map;
	t_game_data	game;

	if (argc != 2 || !ft_file_is_dot_ber(argv[1]))
		return (ft_print_error(ERROR_ARGV), 1);
	map = ft_calloc(1, sizeof(t_map_data));
	if (map == NULL)
		return (ft_print_error(ERROR_MALLOC), 1);
	if (ft_init_map(map, argv[1]))
		return (ft_free_map_struct(map), 1);
	ft_init_game_struct(&game, &map);
	ft_handle_max_map_size(&game);
	if (ft_validate_map(game.map))
		ft_end_game(&game);
	game.mlx_window = mlx_new_window(game.mlx_instance,
			map->width * SPRITE_SIDE_PIXELS,
			map->height * SPRITE_SIDE_PIXELS, "so_long");
	if (game.mlx_window == NULL)
		ft_end_game(&game);
	ft_open_xpms(&game);
	ft_paint_map(&game);
	mlx_key_hook(game.mlx_window, ft_handle_key, &game);
	mlx_hook(game.mlx_window, DestroyNotify, NoEventMask, ft_end_game, &game);
	mlx_loop(game.mlx_instance);
	return (0);
}

void	ft_handle_max_map_size(t_game_data *game)
{
	int	x;
	int	y;

	mlx_get_screen_size(game->mlx_instance, &x, &y);
	if (game->map->width * SPRITE_SIDE_PIXELS > x
		|| game->map->height * SPRITE_SIDE_PIXELS > y)
	{
		ft_print_error(ERROR_MAP_TOO_BIG);
		ft_end_game(game);
	}
}

int	ft_handle_key(int keysym, t_game_data *game)
{
	if (keysym == XK_Escape)
		ft_end_game(game);
	else if (keysym == XK_Down)
		ft_move(game->map, 1, 0, game);
	else if (keysym == XK_Up)
		ft_move(game->map, -1, 0, game);
	else if (keysym == XK_Left)
		ft_move(game->map, 0, -1, game);
	else if (keysym == XK_Right)
		ft_move(game->map, 0, 1, game);
	ft_paint_map(game);
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
		map->collectible--;
	}
	else if (tile == MAP_EXIT && map->collectible == 0)
		ft_end_game(game);
	game->movs++;
	printf("movs %d\n", game->movs);
}

void	ft_paint_map(t_game_data *game)
{
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
				ft_put_sprite(game, game->xpm_player, i, j);
			else if (map[i][j] == MAP_EXIT)
				ft_put_sprite(game, game->xpm_exit, i, j);
			else if (map[i][j] == MAP_WALL)
				ft_put_sprite(game, game->xpm_wall, i, j);
			else if (map[i][j] == MAP_EMPTY)
				ft_put_sprite(game, game->xpm_floor, i, j);
			else if (map[i][j] == MAP_COLLECTIBLE)
				ft_put_sprite(game, game->xpm_collectible, i, j);
			j++;
		}
		i++;
	}
}
