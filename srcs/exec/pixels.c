/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 21:01:30 by fbenech           #+#    #+#             */
/*   Updated: 2026/04/28 00:48:24 by aandreo          ###   ########.fr       */
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

void draw_ray(double rayheight, int n_ray, mlx_image_t *image, t_map *map)
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
