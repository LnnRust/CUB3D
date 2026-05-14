/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:37:40 by fbenech           #+#    #+#             */
/*   Updated: 2026/05/14 22:39:41 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "cub3d.h"


uint32_t	rgb_to_color(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}


void		free_textures(t_tex *texture)
{
	mlx_delete_texture(texture->east);
	mlx_delete_texture(texture->north);
	mlx_delete_texture(texture->south);
	mlx_delete_texture(texture->west);
	free(texture);
}