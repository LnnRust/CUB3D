/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 21:11:09 by fbenech           #+#    #+#             */
/*   Updated: 2026/04/14 19:54:38 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*faut que je trouve comment determiner l'angle du ray*/

void render_rays(t_player *player, t_map *map)
{
	int n_ray;

	if (WIDTH % 2 == 0)
		n_ray = (FOV / 2) / (WIDTH / 2);
	else
		n_ray = (FOV / 2) / ((WIDTH - 1) / 2/*faut que je trouve le moyen de print le pixel du milieu*/);
}