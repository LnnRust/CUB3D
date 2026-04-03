/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:32:48 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/03 22:45:26 by aandreo          ###   ########.fr       */
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
	if (strncmp(line[i], "NO", 2) == 0)
		return (TEX_NO);
	if (strncmp(line[i], "SO", 2) == 0)
		return (TEX_SO);
	if (strncmp(line[i], "WE", 2) == 0)
		return (TEX_WE);
	if (strncmp(line[i], "EA", 2) == 0)
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
		return(ft_putstr_fd("Error: Texture path missing\'n", 2), false);
	path = ft_strdup(&line[i]);
	if(!path)
		return (false);
	trim_path(path);
	if(access(path, R_OK) != 0 || !is_xpm_file(path))
	{
		free(path);
		return (ft_putstr_fd("Error: invalid texture file\n", 2), false);
	}
	map->tex_path[index] = path;
	return (true);
}

bool	parse_color_line(char *line, t_map *map)
{
	int i;
	int k;

	i = 0;
	i = skip_whitespaces(line, 0);
	if(line[i] != 'F' && line[i] != 'C')
		return (ft_putstr_fd("Error: wrong color format\n", 2), false);
	if(line[i] == 'F' && map->floor_color[0] != -1)
		return (ft_putstr_fd("Error: Duplicate floor color\n", 2), false);
	if(line[i] == 'C' && map->ceil_color[0] != -1)
		return (ft_putstr_fd("Error: Duplicate ceiling color\n", 2), false);
	if(line[i + 1] != ' ' && line[i + 1] != '\t')
		return (ft_putstr_fd("Error: wrong color format\n", 2), false);
	i = skip_whitespaces(line, i + 1);
	while(line[i])
	{

	}

}
