/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 10:07:24 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/15 15:00:21 by aandreo          ###   ########.fr       */
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
	if (len < 4 || ft_strncmp(&map_file[len - 4], ".cub", 4) != 0)
		return (ft_putstr_fd("wrong file extension\n", 2), false);
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
	int	i;

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
	if (is_map_char(content[i]))
	{
		if (state == MAP_ENDED)
			return (ERROR);
		return (IN_MAP);
	}
	return (ERROR);
}

// need to fill this -> extract only the map lines and return char **map
char **extract_map(char **content)
{
	int			i;
	int			k;
	int			j;
	int			max;
	e_status	state;
	char		**map;

	max = len_tab(content);
	i = 0;
	k = 0;
	state = BEFORE_CONTENT;
	map = malloc(sizeof(char *) * (max + 1));
	if (!map)
		return (NULL);
	while (i <= max)
	{
		map[i] = NULL;
		i++;
	}
	i = 0;
	while (content[i])
	{
		state = get_state(content[i], state);
		if (state == ERROR)
			return (ft_putstr_fd("Error: Map parsing error\n", 2), free_map(map), NULL);
		j = skip_whitespaces(content[i], 0);
		if (state == IN_MAP && is_map_char(content[i][j]))
		{
			map[k] = ft_strdup(content[i]);
			if (!map[k])
				return (free_map(map), NULL);
			k++;
		}
		i++;
	}
	map[k] = NULL;
	if (k == 0)
		return (ft_putstr_fd("no map found\n", 2), free_map(map), NULL);
	return (map);
}

bool	parse_map(t_game *game, char **av)
{
	char		**mapcpy;
	char		**content;
	e_status	state;
	e_status	new_state;
	int			i;
	int			j;

	i = 0;
	if (!file_is_valid(av[1]))
		return (ft_putstr_fd("Map file error\n", 2), false);
	content = extract_file_content(av[1]);
	if (!content || content[0][0] == '\0')
		return (ft_putstr_fd("Empty file\n", 2), false);
	state = BEFORE_CONTENT;
	while (content[i])
	{
		new_state = get_state(content[i], state);
		if (new_state == ERROR)
			return (ft_putstr_fd("Error: Parsing error\n", 2), free_tab(content), false);
		j = skip_whitespaces(content[i], 0);
		if (new_state == IN_CONFIG)
		{
			if (content[i][j] == 'F' || content[i][j] == 'C')
			{
				if (!parse_color_line(content[i], game->map))
					return (free_tab(content), false);
			}
			else if (is_config_line(content[i]))
			{
				if (!parse_texture_line(content[i], game->map))
					return (free_tab(content), false);
			}
		}
		state = new_state;
		i++;
	}
	if (!init_is_finished(game->map))
		return (free_tab(content), false);
	game->map->map = extract_map(content);
	free_tab(content);
	if (!game->map->map)
		return (false);
	if (map_has_other_chars(game->map->map))
		return (false);
	if (!check_player_count(game->map->map))
		return (ft_putstr_fd("Error: Wrong player number\n", 2), false);
	set_playerpos(game->map->map, game);
	mapcpy = copy_map(game->map->map);
	if (!mapcpy)
		return (false);
	flood_fill(mapcpy, game->player->x, game->player->y);
	if (!check_floodfill(mapcpy))
		return (ft_putstr_fd("Error: Flood fill error\n", 2), free_map(mapcpy), false);
	free_map(mapcpy);
	set_doorpos(game->map->map, game);
	return (true);
}




