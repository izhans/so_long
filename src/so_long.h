/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:50:46 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/13 05:09:24 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

// ERROR MSGS
# define ERROR_MAP_HEIGHT "Map must have at least 3 lines"
# define ERROR_MAP_SAVE "Error saving map"
# define ERROR_MAP_WIDTH "Map must be rectangular and at least have 3 columns"
# define ERROR_MAP_CONTENT "Invalid map content [accepts 01PEC]: there must be \
						1 player [P], 1 exit [E] and at least 1 collectible [C]"
# define ERROR_MAP_NOT_SURROUNDED_BY_WALLS "Map must be surrounded walls [1]"
# define ERROR_MAP_IMPOSSIBLE_WIN "Map is impossible to complete: inaccesible \
						exit or collectibles"
# define ERROR_MALLOC "Error while allocating memory"

// MAP COMPONENTS
# define MAP_COMPONENTS "01CEP"
# define MAP_EXIT 'E'
# define MAP_PLAYER 'P'
# define MAP_COLLECTIBLE 'C'
# define MAP_EMPTY '0'
# define MAP_WALL '1'
# define MAP_VISITED '2'

// MLX EVENTS
# define MLX_CLOSE_WINDOW_BUTTON 17

// SPRITES
# define SPRITE_SIDE_PIXELS 48
# define SPRITE_EXIT "textures/exit.xpm"
# define SPRITE_COLLECTIBLE "textures/collectable.xpm"
# define SPRITE_FLOOR "textures/floor3.xpm"
# define SPRITE_PLAYER "textures/pj3.xpm"
# define SPRITE_WALL "textures/block.xpm"

typedef struct map_data
{
	int		height;
	int		width;
	char	**content;
	int		player;
	int		player_row;
	int		player_col;
	int		exit;
	int		collectionable;
}	t_map_data;

typedef struct game_data
{
	void		*mlx_instance;
	void		*mlx_window;
	t_map_data	*map;
	int			sprite_side;
	void		*xpm_exit;
	void		*xpm_floor;
	void		*xpm_player;
	void		*xpm_wall;
	void		*xpm_collectible;
	int			movs;
}	t_game_data;

// utils.c
int		ft_file_is_dot_ber(char *file);
void	ft_print_error(char *error_msg);
int		ft_make_map_copy(t_map_data	*map, t_map_data *map_copy);
int		ft_end_game(t_game_data *mlx);
void	ft_free_map_struct(t_map_data *map);

// ft_init_map.c
int		ft_init_map(t_map_data *map, char *map_file);

// ft_validate_map.c
int		ft_validate_map(t_map_data	*map);

// ft_flood_fill.c
int		ft_validate_flood_fill(t_map_data *map);

// sprite_utils.c
int		ft_open_xpms(t_game_data *game);
void	ft_close_xpms(t_game_data *game);
void	ft_put_sprite(t_game_data *game, void *sprite, int i, int j);

#endif
