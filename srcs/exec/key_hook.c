/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 06:47:30 by fbenech           #+#    #+#             */
/*   Updated: 2026/05/06 08:27:45 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void update_player_pos(double x, double y, t_player **player)
{
	(*player)->x += x;
	(*player)->y += y;
}

void update_player_plane(double rspeed, t_player **player)
{
	double olddirx;

	olddirx = (*player)->dirx;
	(*player)->dirx = (*player)->dirx * cos(-rspeed) - (*player)->diry * sin(-rspeed);
	(*player)->diry = olddirx * sin(-rspeed) + (*player)->diry * cos(-rspeed);
}