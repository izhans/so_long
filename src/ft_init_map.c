/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:37:41 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/13 03:00:35 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_get_map_height(char *map_file);
static char	**ft_save_map_content(char *map_file, int map_height);
static int	ft_validate_and_get_map_width(char **map, int map_height);

/**
 * @return 1 if error, 0 if map is initalized correctly
 */
int	ft_init_map(t_map_data *map, char *map_file)
{
	// count map lines
	map->height = ft_get_map_height(map_file);
	if (map->height < 3)
		return (ft_print_error(ERROR_MAP_HEIGHT), 1);
	
	// save map lines
	map->content = ft_save_map_content(map_file, map->height);
	if (map->content == NULL)
		return (ft_print_error(ERROR_MAP_SAVE), 1);
	
	// check if map width is always the same
	map->width = ft_validate_and_get_map_width(map->content, map->height);
	if (map->width < 3)
		return (ft_print_error(ERROR_MAP_WIDTH), 1);
	return (0);
}

/**
 * @brief reads the number of lines using gnl
 * @return number of map lines or 0 in case of error
 */
static int	ft_get_map_height(char *map_file)
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

/**
 * @brief copies the content from the map file into the variable it returns
 * @return an allocated array with the map or NULL in case of error
 */
static char	**ft_save_map_content(char *map_file, int map_height)
{
	int		map_fd;
	char	**map;
	char	*line;

	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1)
		return (NULL);
	map = malloc((map_height + 1) * sizeof(char *));
	if (map == NULL)
	{
		close(map_fd);
		return (NULL);
	}
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

/**
 * @brief checks if all the lines have the same width
 * @return map width or 0 in case of error
 */
static int	ft_validate_and_get_map_width(char **map, int map_height)
{
	int i = 0;
	size_t map_width;

	i = 0;
	map_width = ft_strlen(map[i]);
	while (i < map_height)
	{
		if (ft_strlen(map[i]) != map_width) // TODO free map content			
			return (0);
		i++;
	}
	return (map_width);
}
