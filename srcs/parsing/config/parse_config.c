/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:32:48 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/10 01:36:58 by aandreo          ###   ########.fr       */
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

// extracts color code (255,250,200) and converts it to int -> fill map->ceil/floor tab
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

// check for all error conditions about color codes, then calls good helper to fill struct
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
