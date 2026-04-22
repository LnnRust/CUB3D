/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 21:11:09 by fbenech           #+#    #+#             */
/*   Updated: 2026/04/22 22:41:42 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*l'idee c'est que je parte du ray le plus a gauche et que je decale l'angle
avec lequel je calcule le raydirX d'une valeur constante qui depend
du fov (inter_ray), pourquoi pas appeler en recursif en faisait cos(n += inter_ray)*/

// static mlx_image_t *image;


void call_render_ray(t_player *player, t_map *map, mlx_image_t *image)
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
			raydirX = cos((90 - (FOV / 2) + inter_ray) * M_PI / 180);
			raydirY = sin((90 - (FOV / 2) + inter_ray) * M_PI / 180);
		}
		else if (player->direction == 'S')
		{
			raydirX = cos((260 - (FOV / 2) + inter_ray) * M_PI / 180);
			raydirY = sin((260 - (FOV / 2) + inter_ray) * M_PI / 180);
		}
		else if (player->direction == 'E')
		{
			raydirX = cos((0 - (FOV / 2) + inter_ray) * M_PI / 180);
			raydirY = sin((0 - (FOV / 2) + inter_ray) * M_PI / 180);
		}
		else
		{
			raydirX = cos((180 - (FOV / 2) + inter_ray) * M_PI / 180);
			raydirY = sin((180 - (FOV / 2) + inter_ray) * M_PI / 180);
		}
		inter_ray += (double)FOV / WIDTH;
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
		if (side == 0)
			perpwalldist = (sx - deltaX);
		else
			perpwalldist = (sy - deltaY);
		rayheight = (int)(HEIGHT / perpwalldist);
		draw_ray(rayheight, nray, image, map);
		printf("nray = %d\n", nray);
		nray++;
	}
}

// int main(void)
// {
// 	char **map = (char *[]){
// 	"11111111111111111111111111111111111111",
// 	"1E000000000000000000000000000000000001",
// 	"10000000000000000000000000000000000001",
// 	"10000000000000000000000000000000000001",
// 	"10000000000000000000000000000000000001",
// 	"10000000000000000000000000000000000001",
// 	"10000000000000001000000000000000000001",
// 	"1000000000000000D000000000000000000001",
// 	"10000000000000000100000000000000000001",
// 	"10000000000000001000000000000000000001",
// 	"10000000000000000000000000000000000001",
// 	"10000000000000000000000000000000000001",
// 	"10000000000000000000000000000000000001",
// 	"10000000000000000000000000000000000001",
// 	"10000000000000000000000000000000000001",
// 	"10000000000000000000000000000000000001",
// 	"11111111111111111111111111111111111111",
// 	NULL
// 	};
// 	t_player *player;
// 	player = malloc(sizeof(t_player));
// 	t_map *feur;
// 	feur = malloc(sizeof(t_map));
// 	int i = 0;
// 	while (i < 3)
// 		feur->ceil_color[i++] = 0;
// 	i = 0;
// 	while (i < 3)
// 		feur->floor_color[i++] = 0;
// 	feur->map = map;
// 	player->direction = 'E';
// 	set_player(&player);
// }