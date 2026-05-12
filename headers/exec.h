/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felix <felix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 23:45:52 by fbenech           #+#    #+#             */
/*   Updated: 2026/05/12 10:41:52 by felix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "cub3d.h"
#include <MLX42/MLX42.h>
#include <math.h>

#define FOV 90
#define WIDTH 1280
#define HEIGHT 800

typedef struct s_ray
{
	int		nray;
	int		pxly;
	double	deltaX;/*je commence par le ray le plus a gauche dans l'axe de la cam*/
	double	deltaY;
	double	cameraX;
	int		rayheight;
	int		side;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		dstart;
	int		dend;
	double	raydirX;
	double	raydirY;
	double	sx;
	double	sy;
	double	perpwalldist;
	double	inter_ray;	
}	t_ray;

typedef struct s_tex
{
	mlx_texture_t *north;
	mlx_texture_t *south;
	mlx_texture_t *east;
	mlx_texture_t *west;
}	t_tex;

typedef struct s_dda
{
	t_tex *tex;
	t_ray *ray;
}	t_dda;

/*utils.c*/

uint32_t rgb_to_color(int r, int g, int b);

/*pixel.c*/

void render_ray(t_dda *dda, mlx_image_t *image, t_map *map, t_player *player);
void init_tex(t_tex **texture, t_map *map);
void print_texture(t_player *player, t_ray *ray, t_tex *tex, mlx_image_t *image);

/*main.c*/

void set_player(t_player **player, char **map);

/*raycasting.c*/

void call_render_ray(t_player *player, t_map *map, mlx_image_t *image, char **carte);

/*key_hook.c*/

void update_player_pos(double dx, double dy, t_player **player, char **map);
void update_player_plane(double rspeed, t_player **player);
