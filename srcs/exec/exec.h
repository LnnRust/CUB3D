/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 23:45:52 by fbenech           #+#    #+#             */
/*   Updated: 2026/04/21 22:02:58 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"
#define FOV 90
#define WIDTH 1080
#define HEIGHT 720

/*va servir a afficher toutes les range de pixel*/
typedef struct s_cam
{
	int dir;/*center of view of the fov*/
	int camx;/*value between 1 and -1*/
	int camplane;/*width of the fov*/
}	t_cam;

/*utils.c*/

uint32_t rgb_to_color(int r, int g, int b);

/*pixel.c*/

void draw_ray(double rayheight, int n_ray, mlx_image_t *image, t_map *map);

/*main.c*/

void set_player(t_player **player);

/*raycasting.c*/

void call_render_ray(t_player *player, t_map *map);
