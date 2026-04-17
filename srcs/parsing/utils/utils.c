/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:29:20 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/14 23:23:26 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int skip_whitespaces(char *line, int i)
{
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int	count_doors(char **map)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'D')
			{
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

char	**copy_map(char **map)
{
	int		i;
	char	**tmp;

	i = 0;
	while (map[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (map[i])
	{
		tmp[i] = ft_strdup(map[i]);
		if (!tmp[i])
			return (free_tab(tmp), NULL);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

bool	is_xpm_file(char *line)
{
	int len;

	if (!line)
		return (false);
	len = ft_strlen(line);
	if (len < 4)
		return (false);
	if(ft_strncmp(&line[len - 4], ".xpm", 4) != 0)
		return (false);
	return true;
}

bool	is_map_char(char line)
{
	if(line == ' ' || line == 'D'
		|| line == 'E' || line == '1'
		|| line == '0' || line == 'N'
		|| line == 'S' || line == 'E'
		|| line == 'W' || line == '2')
		return(true);
	return (false);
}
