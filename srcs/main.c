/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:01:22 by aandreo           #+#    #+#             */
/*   Updated: 2026/05/14 22:44:19 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "cub3d.h"

static void game_loop(void *param)
{
    t_game *game;
    double  ms = 0.3 * 0.16; 

    game = (t_game *)param;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
        update_player_pos(game->player->dirx * ms, game->player->diry * ms,
            &game->player, game->map->map);
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
        update_player_pos(-game->player->dirx * ms, -game->player->diry * ms,
            &game->player, game->map->map);
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
        update_player_pos(-game->player->plane_x * ms, -game->player->plane_y * ms,
            &game->player, game->map->map);
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
        update_player_pos(game->player->plane_x * ms, game->player->plane_y * ms,
            &game->player, game->map->map);
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        update_player_plane(0.04, &game->player);
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        update_player_plane(-0.04, &game->player);
    call_render_ray(game->player, game->map, (*game->image), game);
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

void set_player(t_player **player, char **map)
{
	int	i;
	int	j;
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S')
			{
				(*player)->x = (double)j + 0.5;
				(*player)->y = (double)i + 0.5;
				break;
			}
			j++;
		}
		i++;
	}
	if ((*player)->direction == 'N')
	{
		(*player)->dirx = 0;
		(*player)->diry = -1;
		(*player)->plane_x = 0.66;
		(*player)->plane_y = 0;
	}
	if ((*player)->direction == 'S')
	{
		(*player)->dirx = 0;
		(*player)->diry = 1;
		(*player)->plane_x = -0.66;
		(*player)->plane_y = 0;
	}
	if ((*player)->direction == 'E')
	{
		(*player)->dirx = 1;
		(*player)->diry = 0;
		(*player)->plane_x = 0;
		(*player)->plane_y = 0.66;
	}
	if ((*player)->direction == 'W')
	{
		(*player)->dirx = -1;
		(*player)->diry = 0;
		(*player)->plane_x = 0;
		(*player)->plane_y = -0.66;
	}
}

int main(int ac, char **av)
{
	t_tex		*tex;
	t_game		*game;
	mlx_image_t	*image;
	int			status;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	if(!init_game(game))
		return (free(game), 1);
	if (ac != 2)
		return (ft_putstr_fd("Usage: ./cub3d <map.cub>\n", 2), free_game(game), free(game), 1);
	if (!parse_map(game, av))
		return (free_game(game), free(game), 1);
	set_player(&game->player, game->map->map);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if(!game->mlx)
		return (free_game(game), free(game), EXIT_FAILURE);
	image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!image)
		return (mlx_terminate(game->mlx), free_game(game), free(game), EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, image, 0, 0) < 0)
		return (mlx_delete_image(game->mlx, image), mlx_terminate(game->mlx), free_game(game), free(game), EXIT_FAILURE);
	game->image = &image;
	tex = malloc(sizeof(t_tex));
	if (!tex)
		return (mlx_delete_image(game->mlx, image), mlx_terminate(game->mlx), free_game(game), free(game), EXIT_FAILURE);
	init_tex(&tex, game->map);
	game->tex = tex;
	call_render_ray(game->player, game->map, image, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate((mlx_t *)game->mlx);
	free_textures(tex);
	free_game(game);
	free(game);
	status = EXIT_SUCCESS;
	return (status);
}


