/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:35:08 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/06 01:56:12 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int ft_valid_component(char c);

int	ft_get_map_height(char *map_file)
{
	int map_fd;
	int map_height;
	char *line;

	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1) // ! open error
		return (0);
	map_height = 0;
	line = get_next_line(map_fd);
	while (line)
	{
		free(line);
		map_height++;
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (map_height);
}

char	**ft_save_map_content(char *map_file, int map_height)
{
	int map_fd;
	char **map;
	char	*line;

	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1) // ! open error
		return (NULL);
	map = malloc((map_height + 1) * sizeof(char *));
	if (map == NULL) // ! malloc error
		return (NULL);
	int i = 0;
	while (i < map_height)
	{
		line = get_next_line(map_fd);
		map[i] = ft_strtrim(line, "\n");
		free(line);
		if (map[i] == NULL)
		{
			ft_free_str_array(map);
			close(map_fd);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	close(map_fd);
	return (map);
}

// ? y si en caso de error setteo width a 0 o -1 y gestiono el error arriba?
int	ft_validate_and_get_map_width(char **map, int map_height)
{
	int i = 0;
	size_t map_width = ft_strlen(map[i]);
	while (i < map_height)
	{
		printf("%s\n", map[i]);
		if (ft_strlen(map[i]) != map_width)
		{
			// frees
			printf("hay lineas que son de distinta longitud\n");
			return (0);
		}
		i++;
	}
	return (map_width);
}

int	ft_validate_components(t_map_data *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->content[i])
	{
		j = 0;
		while (j < map->width)
		{
			if (ft_valid_component(map->content[i][j]))
			{
				if (map->content[i][j] == MAP_EXIT)
					map->exit++;
				else if (map->content[i][j] == MAP_PLAYER)
					map->player++;
				else if (map->content[i][j] == MAP_COLLECTIONABLE)
					map->collectionable++;
			}
			else
				return (1); // ! error
			j++;
		}
		i++;
	}
	return (0);
}

static int ft_valid_component(char c)
{
	return (ft_strchr(MAP_COMPONENTS, c) != NULL);
}

int	ft_validate_outer_walls(t_map_data *map)
{
	int i = 0;
	int last_row = map->height -1;
	int last_col = map->width -1;
	
	while (i < map->width)
	{
		if (map->content[0][i] != '1' || map->content[last_row][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->content[i][0] != '1' || map->content[i][last_col] != '1')
			return (1);
		i++;
	}
	return (0);
}
