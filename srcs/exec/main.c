/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:47:44 by fbenech           #+#    #+#             */
/*   Updated: 2026/04/22 19:51:22 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// int exec(char **map)
// {
// 	t_player *player;/*a remplacer par la struct qui sort du parsing*/
// 	set_player(player);
// 	/*ouvrir une window*/
// 	/*render le fov*/
// 	/*faire la loop pour le game play*/
// 	/*fermer la window et free tout*/
// }

void set_player(t_player **player)
{
	if ((*player)->direction == 'N')
	{
		(*player)->dirx = 0;
		(*player)->diry = -1;
	}
	if ((*player)->direction == 'S')
	{
		(*player)->dirx = 0;
		(*player)->diry = 1;
	}
	if ((*player)->direction == 'E')
	{
		(*player)->dirx = 1;
		(*player)->diry = 0;
	}
	if ((*player)->direction == 'W')
	{
		(*player)->dirx = -1;
		(*player)->diry = 0;
	}
}

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
	(void)av;
	t_game *game;
	int		status;
	char **map = (char *[]){
	"11111111111111111111111111111111111111",
	"1E000000000000000000000000000000000001",
	"10000000000000000000000000000000000001",
	"10000000000000000000000000000000000001",
	"10000000000000000000000000000000000001",
	"10000000000000000000000000000000000001",
	"10000000000000001000000000000000000001",
	"1000000000000000D000000000000000000001",
	"10000000000000000100000000000000000001",
	"10000000000000001000000000000000000001",
	"10000000000000000000000000000000000001",
	"10000000000000000000000000000000000001",
	"10000000000000000000000000000000000001",
	"10000000000000000000000000000000000001",
	"10000000000000000000000000000000000001",
	"10000000000000000000000000000000000001",
	"11111111111111111111111111111111111111",
	NULL
	};

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	if(!init_game(game))
		return (1);
	// if(!parse_map(game, av))
	// 	return (1);
	game->mlx = mlx_init(1300, 900, "Cub3d", true);
	if(!game->mlx)
		return (EXIT_FAILURE);
	t_player *player;
	player = malloc(sizeof(t_player));
	t_map *feur;
	feur = malloc(sizeof(t_map));
	int i = 0;
	while (i < 3)
		feur->ceil_color[i++] = 0;
	i = 0;
	while (i < 3)
		feur->floor_color[i++] = 0;
	feur->map = map;
	player->direction = 'E';
	set_player(&player);
	call_render_ray(player, feur );
	mlx_key_hook((mlx_t *)game->mlx, key_hook, game->mlx);
	mlx_loop((mlx_t *)game->mlx);
	mlx_terminate((mlx_t *)game->mlx);
	// free_game(game);
	free(game);
	status = EXIT_SUCCESS;
	return (status);
}