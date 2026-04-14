/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 10:07:24 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/14 22:48:34 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// update parsing state and return the actual parsing state, returns error if it detects any parsing error
e_status get_state(char *content, e_status state)
{
	int i;

	i = skip_whitespaces(content, 0);
	if (content[i] == '\0')
	{
		if (state == IN_MAP)
			return (MAP_ENDED);
		return (state);
	}
	if (ft_strncmp(&content[i], "NO", 2) == 0
			|| ft_strncmp(&content[i], "SO", 2) == 0
			|| ft_strncmp(&content[i], "WE", 2) == 0
			|| ft_strncmp(&content[i], "EA", 2) == 0
			|| content[i] == 'F' || content[i] == 'C')
	{
		if (state == IN_MAP || state == MAP_ENDED)
			return (ERROR);
		return (IN_CONFIG);
	}
	if (is_map_char(&content[i]))
	{
		if (state == MAP_ENDED)
			return (ERROR);
		return (IN_MAP);
	}
	if (state == BEFORE_CONTENT || state == IN_CONFIG)
		return (ERROR);
	if (state == IN_MAP || state == MAP_ENDED)
		return (ERROR);
	return (ERROR);
}

// need to fill this -> extract only the map lines and return char **map
char **extract_map(char **content)
{

}

bool	parse_map(t_game *game, char **av)
{
	char 		**mapcpy;
	char		**content;
	e_status	state;
	int			i;

	if(!file_is_valid(av[1]))
		return(ft_putstr_fd("Map file error\n", 2), false);
	content = extract_file_content(av[1]);
	if(!content || content[0] == '\0')
		return (ft_putstr_fd("Empty file\n", 2), false);
	state = BEFORE_CONTENT;
	return (true);
	while(content[i])
	{

	}
}




