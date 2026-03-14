/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 10:07:24 by aandreo           #+#    #+#             */
/*   Updated: 2026/03/14 09:24:44 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static bool	file_is_valid(char *map_file)
{
	int	len;
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("map file error", 2), false);
	len = ft_strlen(map_file);
	if (len < 4 || ft_strcmp(&map_file[len - 4], ".cub") != 0)
		return (ft_printf("wrong file extension\n"), false);
	close(fd);
	return (true);
}

static bool	map_has_other_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != 'N'
				&& map[i][j] != 'E' && map[i][j] != '1'
				&& map[i][j] != 'W' && map[i][j] != 'D'
				&& map[i][j] != 'S' && map[i][j] != '2'
				&& map[i][j] != ' ')
				return (ft_putstr_fd("map has invalid characters", 2), true);
			j++;
		}
		i++;
	}
	return (false);
}

static bool	check_player_count(char **map)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E' || map[i][j] == 'S')
				player++;
			if(player > 1)
				return false;
			j++;
		}
		i++;
	}
	if(player != 1)
		return false;
	return true;
}

static char	**copy_map(char **map)
{
	int i;
	char **tmp;

	i = 0;
	while(map[i])
	{
		tmp[i] = ft_strjoin(tmp[i], map[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

bool	parse_map(char **map, t_game *game, char **av)
{
	char **mapcpy;

	if(!file_is_valid(av[1]))
		return(ft_putstr_fd("Map file error\n", 2), false);
	if(!check_player_count(map))
	return (ft_putstr_fd("Wrong player count\n", 2), false);
	if(map_has_other_chars(map))
	return (false);
	mapcpy = copy_map(map);
	flood_fill(mapcpy, game->player->x, game->player->y);
	if(!check_floodfill(mapcpy))
		return (ft_putstr_fd("Flood fill error\n", 2), free_map(mapcpy), false);
	free_map(mapcpy);
	return (true);
}



