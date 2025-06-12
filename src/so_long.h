/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:50:46 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/12 18:48:50 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

# define MAP_COMPONENTS "01CEP"
# define MAP_EXIT 'E'
# define MAP_PLAYER 'P'
# define MAP_COLLECTIBLE 'C'
# define MAP_EMPTY '0'
# define MAP_WALL '1'
# define MAP_VISITED '2'

# define MLX_CLOSE_WINDOW_BUTTON 17

# define SPRITE_SIDE_PIXELS 48
# define SPRITE_EXIT "textures/exit.xpm"
# define SPRITE_COLLECTIBLE "textures/collectable.xpm"
# define SPRITE_FLOOR "textures/floor3.xpm"
# define SPRITE_PLAYER "textures/pj1.xpm"
# define SPRITE_WALL "textures/block.xpm"

typedef struct map_data
{
	int	height;
	int width;
	char **content;
	int player;
	int player_row;
	int player_col;
	int exit;
	int collectionable;
} t_map_data;

typedef struct game_data
{
	void		*mlx_instance;
	void		*mlx_window;
	t_map_data	*map;
	int			sprite_side;
	void		*xmp_exit;
	void		*xmp_floor;
	void		*xmp_player;
	void		*xmp_wall;
	void		*xmp_collectible;
} t_game_data;


int	ft_get_map_height(char *map_file);
char	**ft_save_map_content(char *map_file, int map_height);
int	ft_validate_and_get_map_width(char **map, int map_height);
int	ft_validate_components(t_map_data *map);
int	ft_validate_outer_walls(t_map_data *map);
void	ft_flood_fill(t_map_data *map, int row, int col);
void	ft_free_map_struct(t_map_data *map);

#endif
