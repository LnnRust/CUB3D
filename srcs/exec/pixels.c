/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 21:01:30 by fbenech           #+#    #+#             */
/*   Updated: 2026/05/13 20:16:05 by fbenech          ###   ########.fr       */
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

void render_ray(t_dda *dda, mlx_image_t *image, t_map *map, t_player *player)
{
	dda->ray->pxly = 0;
	dda->ray->dstart = -dda->ray->rayheight / 2 + HEIGHT / 2;
	if (dda->ray->dstart < 0)
		dda->ray->dstart = 0;
	dda->ray->dend = dda->ray->rayheight / 2 + HEIGHT / 2;
	if (dda->ray->dend >= HEIGHT)
		dda->ray->dend = HEIGHT - 1;
	while (dda->ray->pxly < dda->ray->dstart && dda->ray->pxly < HEIGHT)
	{
		ft_mlx_put_pixel(image, dda->ray->nray, dda->ray->pxly, map->floor_color);
		dda->ray->pxly++;
	}
	print_texture(player, dda->ray, dda->tex, image);
	dda->ray->pxly = dda->ray->dend;
	while(dda->ray->pxly < HEIGHT)
	{
		ft_mlx_put_pixel(image, dda->ray->nray, dda->ray->pxly, map->ceil_color);
		dda->ray->pxly++;
	}
}

void print_texture(t_player *player, t_ray *ray, t_tex *tex, mlx_image_t *image)
{
	mlx_texture_t	*texture;
	double			texpos;
	uint32_t		*pixels;
	uint32_t		color;
	double			wallx;
	double			step;
	int				texx; /*horizontal location in the texture*/
	int				texy;
	int				y;

	if (ray->side == 0)
		wallx = player->y + ray->perpwalldist * ray->raydirY;
	else
		wallx = player->x + ray->perpwalldist *ray->raydirX;
	wallx -= floor(wallx);
	if (ray->side == 0 && ray->raydirX > 0)
		texture = tex->west;
	else if (ray->side == 0 && ray->raydirX < 0)
		texture = tex->east;
	else if (ray->side == 1 && ray->raydirY > 0)
		texture = tex->north;
	else
		texture = tex->south;
	texx = (int)(wallx * texture->width);
	step = (double)texture->height / ray->rayheight;
	texpos = (ray->dstart - HEIGHT / 2 + ray->rayheight / 2) * step;
	y = ray->dstart;
	while (y < ray->dend)
	{
		texy = (int)texpos % texture->height;
		pixels = (uint32_t *)texture->pixels;
		color = pixels[texture->width * texy + texx];
		mlx_put_pixel(image, ray->nray, ray->pxly, color);
		texpos += step;
		ray->pxly++;
		y++;
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

