/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:50:50 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/12 18:18:56 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_file_is_dot_ber(char *file);
int	ft_init_map(t_map_data	*map, char *map_file);
void ft_print_error(char *error_msg);
int ft_handle_key(int keysym, t_game_data *mlx);
void	ft_paint_map(t_game_data *game);
int	ft_end_game(t_game_data *mlx);

int main(int argc, char *argv[])
{
	t_map_data	*map;
	t_game_data	mlx;
	
	// check map arg exists + check if .ber
	if (argc != 2 || !ft_file_is_dot_ber(argv[1]))
		return (1);
	
	map = ft_calloc(1, sizeof(t_map_data)); // TODO check errors or pass to non dinamic memory
	if (ft_init_map(map, argv[1]))
		return (ft_free_map_struct(map), 1);
	printf("mapa bien\n");

	// TODO check mlx_data creation errors
	mlx.mlx_instance = mlx_init();
	mlx.mlx_window = mlx_new_window(mlx.mlx_instance, map->width * SPRITE_SIDE_PIXELS,
		map->height * SPRITE_SIDE_PIXELS, "so_long");
	
	mlx.map = map;

	mlx.xmp_exit = mlx_xpm_file_to_image(mlx.mlx_instance, SPRITE_EXIT, &mlx.sprite_side, &mlx.sprite_side);
	mlx.xmp_collectible = mlx_xpm_file_to_image(mlx.mlx_instance, SPRITE_COLLECTIBLE, &mlx.sprite_side, &mlx.sprite_side);
	mlx.xmp_player = mlx_xpm_file_to_image(mlx.mlx_instance, SPRITE_PLAYER, &mlx.sprite_side, &mlx.sprite_side);
	mlx.xmp_wall = mlx_xpm_file_to_image(mlx.mlx_instance, SPRITE_WALL, &mlx.sprite_side, &mlx.sprite_side);
	mlx.xmp_floor = mlx_xpm_file_to_image(mlx.mlx_instance, SPRITE_FLOOR, &mlx.sprite_side, &mlx.sprite_side);

	if (mlx.xmp_exit == NULL)
		return (ft_print_error("Error al pasar el xmp de exit"), 1);

	ft_paint_map(&mlx);

	mlx_key_hook(mlx.mlx_window, ft_handle_key, &mlx);
	mlx_hook(mlx.mlx_window, MLX_CLOSE_WINDOW_BUTTON, NoEventMask, ft_end_game, &mlx);
	
	mlx_loop(mlx.mlx_instance); // ? si no hay ventana se acaba el loop ?
		
	// free map + map data
	ft_free_map_struct(map);
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
	t_map_data	map_copy;

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
	
	// make copy for flood fill
	map_copy = *map;
	ft_flood_fill(&map_copy, map_copy.player_row, map_copy.player_col);
	if (map_copy.exit != 0 || map_copy.player != 0 || map_copy.collectionable != 0)
	{
		printf("error despues de flood fill - remains exit: %d player: %d collectionables: %d\n", map_copy.exit, map_copy.player, map_copy.collectionable);
		return (ft_print_error("Inaccesible exit or collectibles"), 1);
	}

	return (0);
}

void ft_print_error(char *error_msg)
{
	printf("Error\n");
	printf("%s\n", error_msg);
}

int ft_handle_key(int keysym, t_game_data *mlx)
{
	printf("pressed %d\n", keysym);
	if (keysym == XK_Escape)
		ft_end_game(mlx);
	
	return (0);
}

void	ft_paint_map(t_game_data *game)
{
	printf("ft_paint_map\n");
	int		i;
	int		j;
	char	**map = game->map->content;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (map[i][j] == MAP_EXIT)
				mlx_put_image_to_window(game->mlx_instance, game->mlx_window, game->xmp_exit, i * SPRITE_SIDE_PIXELS, j * SPRITE_SIDE_PIXELS);
			else if (map[i][j] == MAP_WALL)
				mlx_put_image_to_window(game->mlx_instance, game->mlx_window, game->xmp_wall, i * SPRITE_SIDE_PIXELS, j * SPRITE_SIDE_PIXELS);
			else if (map[i][j] == MAP_EMPTY)
				mlx_put_image_to_window(game->mlx_instance, game->mlx_window, game->xmp_floor, i * SPRITE_SIDE_PIXELS, j * SPRITE_SIDE_PIXELS);
			else if (map[i][j] == MAP_PLAYER)
				mlx_put_image_to_window(game->mlx_instance, game->mlx_window, game->xmp_player, i * SPRITE_SIDE_PIXELS, j * SPRITE_SIDE_PIXELS);
			else if (map[i][j] == MAP_COLLECTIBLE)
				mlx_put_image_to_window(game->mlx_instance, game->mlx_window, game->xmp_collectible, i * SPRITE_SIDE_PIXELS, j * SPRITE_SIDE_PIXELS);
			j++;
		}
		i++;
	}
	
	
}

int	ft_end_game(t_game_data *mlx)
{
	mlx_destroy_window(mlx->mlx_instance, mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_instance);
	free(mlx->mlx_instance);
	ft_free_map_struct(mlx->map);
	exit(0);
	return (0);
}
