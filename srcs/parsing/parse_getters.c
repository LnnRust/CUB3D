/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:32:48 by aandreo           #+#    #+#             */
/*   Updated: 2026/03/30 15:06:42 by aandreo          ###   ########.fr       */
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
