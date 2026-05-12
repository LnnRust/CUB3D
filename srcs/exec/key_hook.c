/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felix <felix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 06:47:30 by fbenech           #+#    #+#             */
/*   Updated: 2026/05/12 10:41:34 by felix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "exec.h"

void update_player_pos(double dx, double dy, t_player **player, char **map)
{
	double  newx;
	double  newy;
	
	newx = (*player)->x + dx;
	newy = (*player)->y + dy;
	if (map[(int)(*player)->y][(int)newx] != '1')
		(*player)->x = newx;
	if (map[(int)newy][(int)(*player)->x] != '1')
		(*player)->y = newy;
}

void update_player_plane(double rspeed, t_player **player)
{
	double olddirx;
	double odlplanex;

	olddirx = (*player)->dirx;
	(*player)->dirx = (*player)->dirx * cos(-rspeed) - (*player)->diry * sin(-rspeed);
	(*player)->diry = olddirx * sin(-rspeed) + (*player)->diry * cos(-rspeed);
	odlplanex = (*player)->plane_x;
	(*player)->plane_x = (*player)->plane_x * cos(-rspeed) - (*player)->plane_y * sin(-rspeed);
	(*player)->plane_y = odlplanex * sin(-rspeed) + (*player)->plane_y * cos(-rspeed);
}