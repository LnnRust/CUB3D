/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 21:01:30 by fbenech           #+#    #+#             */
/*   Updated: 2026/04/28 23:26:41 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void ft_mlx_put_pixel(mlx_image_t *image, int x, int y, int *rgb)
{
	uint32_t color;

	color = rgb_to_color(rgb[0], rgb[1], rgb[2]);
	if (x > WIDTH || x < 0 || y > HEIGHT || y < 0)
		return ;
	mlx_put_pixel(image, x, y, color);
}

/*faire une fonction qui determine comment afficher le mur en fonction de la distance*/

void render_ray(double rayheight, int n_ray, mlx_image_t *image, t_map *map)
{
	int pxly;
	int dstart;
	int dend;
	pxly = 0;
	int white[3] = {255, 255, 255};
	int idk[3] = {175, 100, 175};

	dstart = -rayheight / 2 + HEIGHT / 2;
	if (dstart < 0)
		dstart = 0;
	dend = rayheight / 2 + HEIGHT / 2;
	if (dend >= HEIGHT)
		dend = HEIGHT - 1;
	while (pxly < dstart && pxly < HEIGHT)
	{
		ft_mlx_put_pixel(image, n_ray, pxly, white);
		pxly++;
	}
	while (pxly < dend && pxly < HEIGHT)
	{
		ft_mlx_put_pixel(image, n_ray, pxly, idk);
		pxly++;
	}
	while(pxly < HEIGHT)
	{
		ft_mlx_put_pixel(image, n_ray, pxly, map->ceil_color);
		pxly++;
	}
}

int *get_color(t_player *player, t_ray *ray, t_tex *tex)
{
	double	wallX;
	int		tenX; /*horizontal location in the texture*/
	int		texture;

	if (ray->side == 0)
		wallX = player->y + ray->perpwalldist * ray->raydirY;
	else
		wallX = player->x + ray->perpwalldist *ray->raydirX;
	wallX -= floor(wallX);
	if (ray->side == 0 && ray->raydirX > 0)
	{
		texture = TEX_WE;
		tenX = (int)(wallX * tex->west->width);
	}
	else if (ray->side == 0 && ray->raydirX < 0)
	{
		texture = TEX_EA;
		tenX = (int)(wallX * tex->east->width);
	}
	else if (ray->side == 1 && ray->raydirY > 0)
	{
		texture = TEX_NO;
		tenX = (int)(wallX * tex->north->width);
	}
	else
	{
		texture = TEX_SO;
		tenX = (int)(wallX * tex->south->width);
	}
}

void	init_tex(t_tex **texture, t_map *map)
{
	(*texture) = malloc(sizeof(t_tex));
	if (!(*texture))
		return ;
	(*texture)->north = mlx_load_png(map->tex_path[TEX_NO]);
	(*texture)->south = mlx_load_png(map->tex_path[TEX_SO]);
	(*texture)->east = mlx_load_png(map->tex_path[TEX_EA]);
	(*texture)->west = mlx_load_png(map->tex_path[TEX_WE]);
}

