/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 21:11:09 by fbenech           #+#    #+#             */
/*   Updated: 2026/04/21 19:01:16 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*l'idee c'est que je parte du ray le plus a gauche et que je decale l'angle
avec lequel je calcule le raydirX d'une valeur constante qui depend
du fov (inter_ray), pourquoi pas appeler en recursif en faisait cos(n += inter_ray)*/

static mlx_image_t *image;


void call_render_ray(t_player *player, t_map *map)
{
	int		nray;
	double	deltaX;/*je commence par le ray le plus a gauche dans l'axe de la cam*/
	double	deltaY;
	int		rayheight;
	int		side;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	double	raydirX;
	double	raydirY;
	double	sx;
	double	sy;
	double	perpwalldist;
	double	inter_ray;

	inter_ray = 0.0;
	nray = 0;
	while (nray < WIDTH)
	{
		mapX = (int)player->x;
		mapY = (int)player->y;
		if (player->direction == 'N')
		{
			raydirX = cos(90 - (FOV / 2) + inter_ray);
			raydirY = sin(90 - (FOV / 2) + inter_ray);
		}
		else if (player->direction == 'S')
		{
			raydirX = cos(260 - (FOV / 2) + inter_ray);
			raydirY = sin(260 - (FOV / 2) + inter_ray);
		}
		else if (player->direction == 'E')
		{
			raydirX = cos(0 - (FOV / 2) + inter_ray);
			raydirY = sin(0 - (FOV / 2) + inter_ray);
		}
		else
		{
			raydirX = cos(180 - (FOV / 2) + inter_ray);
			raydirY = sin(180 - (FOV / 2) + inter_ray);
		}
		inter_ray = FOV / WIDTH;
		deltaX = fabs(1 / raydirX);
		deltaY = fabs(1 / raydirY);
		if (raydirX < 0)
		{
			stepX = -1;
			sx = (player->x - (int)player->x) * deltaX;
		}
		else
		{
			stepX = 1;
			sx = ((int)player->x + 2 - player->x) * deltaX;
		}
		if (raydirY < 0)
		{
			stepY = -1;
			sy = (player->y - (int)player->y) *deltaX;
		}
		else
		{
			stepY = 1;
			sy = ((int)player->y + 1.0 - player->y) * deltaY;
		}
		while(map->map[mapX][mapY] == 0)
		{
			if (sx > sy)
			{
				sx += deltaX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sy += deltaY;
				mapY += stepY;
				side = 1;
			}
		}
		nray++;
		if (side == 0)
			perpwalldist = (sx - deltaX);
		else
			perpwalldist = (sy - deltaY);
		rayheight = (int)(HEIGHT / perpwalldist);
		draw_ray(rayheight, nray, image, map);
	}
}

int main(void)
{
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
	t_player *player;
	player = malloc(sizeof(t_player));
	t_map *game;
	game = malloc(sizeof(t_map));
	int i = 0;
	while (i < 3)
		game->ceil_color[i++] = 0;
	i = 0;
	while (i < 3)
		game->floor_color[i++] = 0;
	game->map = map;
	player->direction = 'E';
	set_player(&player);
}