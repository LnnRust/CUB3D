/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 01:33:16 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/13 05:19:49 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	is_config_line(char *line)
{
    int	i;

    i = skip_whitespaces(line, 0);
    if (line[i] == '\0')
        return (false);
    if ((ft_strncmp(&line[i], "NO", 2) == 0
            || ft_strncmp(&line[i], "SO", 2) == 0
            || ft_strncmp(&line[i], "WE", 2) == 0
            || ft_strncmp(&line[i], "EA", 2) == 0)
        && (line[i + 2] == ' ' || line[i + 2] == '\t'))
        return (true);
    if ((line[i] == 'F' || line[i] == 'C')
        && (line[i + 1] == ' ' || line[i + 1] == '\t'))
        return (true);
    return (false);
}