/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 01:30:52 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/10 22:38:27 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_doorpos(char **map, t_game *game)
{
	int i;
	int j;
	int k;

	game->map->door_count = count_doors(map);
	if(game->map->door_count < 1)
		return ;
	game->map->doors = malloc(sizeof(t_door) * game->map->door_count);
	if(!game->map->doors)
		return ;
	i = 0;
	k = 0;
	while(map[i++])
	{
		j = 0;
		while(map[i][j++])
		{
			if(map[i][j] == 'D')
			{
				game->map->doors[k].x = j;
				game->map->doors[k].y = i;
				game->map->doors[k].open = false;
				k++;
			}
		}
	}
}

void	set_playerpos(char **map, t_game *game)
{
	int i;
	int j;
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				game->player->direction = map[i][j];
				game->player->x = j;
				game->player->y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}
