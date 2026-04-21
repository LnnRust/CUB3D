/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:47:44 by fbenech           #+#    #+#             */
/*   Updated: 2026/04/21 19:01:16 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


int exec(char **map)
{
	t_player *player;/*a remplacer par la struct qui sort du parsing*/
	set_player(player);
	/*ouvrir une window*/
	/*render le fov*/
	/*faire la loop pour le game play*/
	/*fermer la window et free tout*/
}

void set_player(t_player **player)
{
	if ((*player)->direction == 'N')
	{
		(*player)->dirx = 0;
		(*player)->diry = -1;
	}
	if ((*player)->direction == 'S')
	{
		(*player)->dirx = 0;
		(*player)->diry = 1;
	}
	if ((*player)->direction == 'E')
	{
		(*player)->dirx = 1;
		(*player)->diry = 0;
	}
	if ((*player)->direction == 'W')
	{
		(*player)->dirx = -1;
		(*player)->diry = 0;
	}
}
