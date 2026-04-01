/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:01:22 by aandreo           #+#    #+#             */
/*   Updated: 2026/03/31 17:52:16 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static void	init_tmap(t_map *map)
{
	map->map = NULL;
	map->width = -1;
	map->height = -1;
	map->door_count = -1;
	map->doors = NULL;
	map->sprite_count = -1;
	map->sprites = NULL;
	map->tex_path[0] = NULL;
	map->tex_path[1] = NULL;
	map->tex_path[2] = NULL;
	map->tex_path[3] = NULL;
	map->tex_path[4] = NULL;
	map->floor_color[0] = -1;
	map->floor_color[1] = -1;
	map->floor_color[2] = -1;
	map->ceil_color[0] = -1;
	map->ceil_color[1] = -1;
	map->ceil_color[2] = -1;
}

static bool	init_game(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if(!game->map)
		return (false);
	game->player = malloc(sizeof(t_player));
	if(!game->player)
		return (false);
	init_tmap(game->map);
	game->player->x = -1;
	game->player->y = -1;
	game->player->direction = '\0';
	return (true);
}
void free_game(t_game *game)
{
	int i;

	i = 0;
	if(!game)
		return ;
	if(game->map)
	{
		while(i < TEX_COUNT - 1)
		{
			free(game->map->tex_path[i]);
			i++;
		}
		free_map(game->map->map);
		free(game->map->doors);
		free(game->map->sprites);
	}
	if(game->player)
		free(game->player);
}

int main(int ac, char **av)
{
	if(ac == 2)
	{
		t_game *game;
		game = malloc(sizeof(t_game));
		if (!game)
			return (1);
		if(init_game(game) == false)
			return (1);
		char **test = extract_file_content(av[1]);
		char *tmp = get_texture_path(test, "NO");
		printf("%s", tmp);
		return (0);
	}
	printf("Wrong args: Valid args -> ./cub3d map.cub\n");
	return (0);
}
