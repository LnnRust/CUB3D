/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 10:08:12 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/15 15:02:04 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static bool	is_border(char **map, int x, int y)
{
	if (!map || x < 0 || y < 0)
		return (true);
	if (!map[y])
		return (true);
	if ((size_t)x >= ft_strlen(map[y]))
		return (true);
	if (map[y][x] == ' ' || map[y][x] == '\t')
		return (true);
	return (false);
}

void	flood_fill(char **map, int x, int y)
{
	if(is_border(map, x, y))
		return ;
	if(map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x - 1, y);
	flood_fill(map, x + 1, y);
	flood_fill(map, x, y - 1);
	flood_fill(map, x, y + 1);
}

bool	check_floodfill(char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == '0' || map[i][j] == '2'
				|| map[i][j] == 'D')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
