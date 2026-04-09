/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:32:48 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/10 01:25:19 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

size_t find_len(char *path, size_t j)
{
	while(path[j])
	{
		j++;
	}
	return (j);
}

char *get_texture_path(char **map, char *texture)
{
	int i;
	int k;
	size_t j;
	char *ret;

	i = 0;
	while (map[i])
	{
		if (ft_strncmp(map[i], texture, 2) == 0)
		{
			j = find_len(map[i], 4);
			ret = malloc(j + 1);
			if (!ret)
				return (NULL);
			k = 0;
			j = 4;
			while (map[i][j])
				ret[k++] = map[i][j++];
			ret[k] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}

static int	get_texture_index(char *line, int i)
{
	if (strncmp(&line[i], "NO", 2) == 0)
		return (TEX_NO);
	if (strncmp(&line[i], "SO", 2) == 0)
		return (TEX_SO);
	if (strncmp(&line[i], "WE", 2) == 0)
		return (TEX_WE);
	if (strncmp(&line[i], "EA", 2) == 0)
		return (TEX_EA);
	return (-1);
}

static int skip_whitespaces(char *line, int i)
{
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

static void	trim_path(char *line)
{
	int len;

	len = ft_strlen(line);
	while(len && (line[len - 1] == ' ' || line[len - 1] == '\t'))
	{
		line[len - 1] = '\0';
		len--;
	}
}

//check for any parsing error, and copy the ./file/file.xpm path into the map->tex_path
bool	parse_texture_line(char *line, t_map *map)
{
	int i;
	int	index;
	char *path;

	i = skip_whitespaces(line, 0);
	index = get_texture_index(line, i);
	if(index < 0)
		return (false);
	if(line[i + 2] != ' ' && line[i + 2] != '\t')
		return (ft_putstr_fd("Error: wrong texture format\n", 2), false);
	if(map->tex_path[index] != NULL)
		return(ft_putstr_fd("Error: duplicate token\n", 2), false);
	i = skip_whitespaces(line, i + 2);
	if(line[i] == '\0')
		return(ft_putstr_fd("Error: Texture path missing\n", 2), false);
	path = ft_strdup(&line[i]);
	if(!path)
		return (false);
	trim_path(path);
	if(access(path, R_OK) != 0 || !is_xpm_file(path))
	{
		free(path);
		return (ft_putstr_fd("Error: invalid texture file\n", 2), false);
	}
	return (map->tex_path[index] = path, true);
}

bool	extract_rgb_code(t_map *map, char *line, int i, char code)
{
	char **dest;
	int j;
	int k;

	j = 0;
	dest = ft_split(&line[i], ',');
	if(!dest || dest[3])
		return (free_tab(dest), false);
	while(j < 3)
	{
		k = 0;
		if(dest[j][0] == '\0')
			return (free_tab(dest), false);
		while(dest[j][k])
		{
			if(dest[j][k] != ' ' && dest[j][k] != '\t' && !ft_isdigit(dest[j][k]))
				return (free_tab(dest), false);
			k++;
		}
		if(ft_atoi(dest[j]) < 0 || ft_atoi(dest[j]) > 255)
			return (free_tab(dest), false);
		if(code == 'F')
			map->floor_color[j] = ft_atoi(dest[j]);
		else
			map->ceil_color[j] = ft_atoi(dest[j]);
		j++;
	}
	return (free_tab(dest), true);
}

static bool	fill_ceil_color(char *line, t_map *map, int i)
{
	if(!extract_rgb_code(map, line, i, 'C'))
		return (ft_putstr_fd("Ceiling color error\n", 2), false);
	return(true);
}

static bool	fill_floor_color(char *line, t_map *map, int i)
{
	if(!extract_rgb_code(map, line, i, 'F'))
		return (ft_putstr_fd("Floor color error\n", 2), false);
	return(true);
}

bool	parse_color_line(char *line, t_map *map)
{
	int i;
	int j;

	i = 0;
	i = skip_whitespaces(line, 0);
	j = i;
	if(line[i] != 'F' && line[i] != 'C')
		return (ft_putstr_fd("Error: wrong color format\n", 2), false);
	if(line[i] == 'F' && map->floor_color[0] != -1)
		return (ft_putstr_fd("Error: Duplicate floor color\n", 2), false);
	if(line[i] == 'C' && map->ceil_color[0] != -1)
		return (ft_putstr_fd("Error: Duplicate ceiling color\n", 2), false);
	if(line[i + 1] != ' ' && line[i + 1] != '\t')
		return (ft_putstr_fd("Error: wrong color format\n", 2), false);
	i = skip_whitespaces(line, i + 1);
	if(line[j] == 'F')
	{
		if(!fill_floor_color(line, map, i))
			return (false);
	}
	else
		if(!fill_ceil_color(line, map, i))
			return (false);
	return (true);
}
