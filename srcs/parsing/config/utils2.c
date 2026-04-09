/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 01:33:16 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/10 01:35:34 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

bool	fill_ceil_color(char *line, t_map *map, int i)
{
	if(!extract_rgb_code(map, line, i, 'C'))
		return (ft_putstr_fd("Ceiling color error\n", 2), false);
	return(true);
}

bool	fill_floor_color(char *line, t_map *map, int i)
{
	if(!extract_rgb_code(map, line, i, 'F'))
		return (ft_putstr_fd("Floor color error\n", 2), false);
	return(true);
}

int	get_texture_index(char *line, int i)
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
