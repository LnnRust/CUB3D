/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 21:11:09 by fbenech           #+#    #+#             */
/*   Updated: 2026/05/14 22:41:23 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*l'idee c'est que je parte du ray le plus a gauche et que je decale l'angle
avec lequel je calcule le raydirX d'une valeur constante qui depend
du fov (inter_ray), pourquoi pas appeler en recursif en faisait cos(n += inter_ray)*/


static void	def_ray(t_ray **ray, t_player *player)
{
	(*ray)->mapX = (int)player->x;
	(*ray)->mapY = (int)player->y;
	(*ray)->cameraX = 2 * (*ray)->nray / (double)WIDTH - 1;
	(*ray)->raydirX = player->dirx + player->plane_x * (*ray)->cameraX;
	(*ray)->raydirY = player->diry + player->plane_y * (*ray)->cameraX;
	(*ray)->inter_ray += (double)FOV / WIDTH;
	(*ray)->deltaX = fabs(1 / (*ray)->raydirX);
	(*ray)->deltaY = fabs(1 / (*ray)->raydirY);
}

static void	def_ray_and_step(t_ray **ray, t_player *player)
{
	if ((*ray)->raydirX < 0)
	{
		(*ray)->stepX = -1;
		(*ray)->sx = (player->x - (int)player->x) * (*ray)->deltaX;
	}
	else
	{
		(*ray)->stepX = 1;
		(*ray)->sx = ((int)player->x + 1.0 - player->x) * (*ray)->deltaX;
	}
	if ((*ray)->raydirY < 0)
	{
		(*ray)->stepY = -1;
		(*ray)->sy = (player->y - (int)player->y) *(*ray)->deltaY;
	}
	else
	{
		(*ray)->stepY = 1;
		(*ray)->sy = ((int)player->y + 1.0 - player->y) * (*ray)->deltaY;
	}
}

static void	init_stuf(t_ray **ray, t_dda **dda, t_tex *tex)
{
	(*ray) = malloc(sizeof(t_ray));
	(*dda) = malloc(sizeof(t_dda));
	(*dda)->tex = tex;
	if (!(*ray) || !(*dda) || !(*dda)->tex)
		return ;
	(*ray)->inter_ray = 0.0;
	(*ray)->nray = 0;
	(*dda)->ray = (*ray);
}

static void	while_loop(t_map *map, t_ray **ray)
{
	while(map->map[(*ray)->mapY][(*ray)->mapX] != '1')
	{
		if ((*ray)->sx < (*ray)->sy)
		{
			(*ray)->sx += (*ray)->deltaX;
			(*ray)->mapX += (*ray)->stepX;
			(*ray)->side = 0;
		}
		else
		{
			(*ray)->sy += (*ray)->deltaY;
			(*ray)->mapY += (*ray)->stepY;
			(*ray)->side = 1;
		}
	}
}

void	call_render_ray(t_player *player, t_map *map, mlx_image_t *image, t_game *game)
{
	t_ray *ray;
	t_dda *dda;

	ft_memset(image->pixels, 0, image->width * image->height * sizeof(uint32_t));
	init_stuf(&ray, &dda, game->tex);
	while (ray->nray < WIDTH)
	{
		def_ray(&ray, player);
		def_ray_and_step(&ray, player);
		while_loop(map, &ray);
		if (ray->side == 0)
			ray->perpwalldist = (ray->sx - ray->deltaX);
		else
			ray->perpwalldist = (ray->sy - ray->deltaY);
		if (ray->perpwalldist <= 0)
			ray->perpwalldist = 0.0001;
		ray->rayheight = (int)(HEIGHT / ray->perpwalldist);
		render_ray(dda, image, map, player);
		ray->nray++;
	}
	free(ray);
	free(dda);
}
