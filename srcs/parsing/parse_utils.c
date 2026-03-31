/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:29:20 by aandreo           #+#    #+#             */
/*   Updated: 2026/03/31 18:57:27 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'D')
			{
				game->map->doors[k].x = j;
				game->map->doors[k].y = i;
				game->map->doors[k].open = false;
				k++;
			}
			j++;
		}
		i++;
	}
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	ft_strcat(result, s1);
	ft_strcat(result, s2);
	return (result);
}

bool	is_xpm_file(char *line)
{
	int len;

	len = ft_strlen(line);
	if(ft_strncmp(line[len - 4], ".xpm", 4) != 0)
		return (false);
	return true;
}

bool	is_map_char(char *line)
{
	if(line[0] == ' ' || line[0] == 'D'
		|| line[0] == 'E' || line[0] == '1'
		|| line[0] == '0' || line[0] == 'N'
		|| line[0] == 'S' || line[0] == 'E'
		|| line[0] == 'W' || line[0] == '2')
		return(true);
	return (false);
}
