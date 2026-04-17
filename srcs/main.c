/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:01:22 by aandreo           #+#    #+#             */
/*   Updated: 2026/04/17 21:34:11 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
# include <MLX42/MLX42.h>

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

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
	game->mlx = NULL;
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
	(void)ac;
	t_game *game;
	int		status;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	if(!init_game(game))
		return (1);
	if(!parse_map(game, av))
		return (1);
	game->mlx = mlx_init(1300, 900, "Cub3d", true);
	if(!game->mlx)
		return (EXIT_FAILURE);
	mlx_key_hook((mlx_t *)game->mlx, key_hook, game->mlx);
	mlx_loop((mlx_t *)game->mlx);
	mlx_terminate((mlx_t *)game->mlx);
	free_game(game);
	free(game);
	status = EXIT_SUCCESS;
	return (status);
}

