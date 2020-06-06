/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 21:17:49 by adbenoit          #+#    #+#             */
/*   Updated: 2020/06/06 22:07:25 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	win_life(t_all **all)
{
	int i;
	int x;
	int y;

	i = 0;
	x = (int)(*all)->player.pos[X];
	y = (int)(*all)->player.pos[Y];
	while (i < (*all)->sp.count)
	{
		if (x == (int)(*all)->sp.coor[i][X] && y == (int)(*all)->sp.coor[i][Y]
		&& (*all)->sp.dead[i] == FALSE && (*all)->sp.type[i] == OBJ)
		{
			if ((*all)->bonus.life < 4)
				(*all)->bonus.life += 2;
			else if ((*all)->bonus.life == 4)
				(*all)->bonus.life++;
			(*all)->sp.dead[i] = 1;
			(*all)->bonus.col = 0;
		}
		i++;
	}
}

static void	lose_life(t_all **all, char c)
{
	int i;

	i = -1;
	if (c == OBJ1 && (*all)->bonus.loop2 > 35 &&
	(*all)->bonus.life > 0 && (*all)->sp.dead[i] == FALSE)
	{
		(*all)->bonus.life--;
		(*all)->bonus.col = 100;
		(*all)->bonus.loop2 = 0;
	}
	else
	{
		while (++i < (*all)->sp.count)
		{
			if ((*all)->sp.see[i] == TRUE && (*all)->sp.type[i] == OBJ1
			&& (*all)->sp.dead[i] == FALSE && (*all)->bonus.loop2 > 60
			&& (*all)->bonus.life > 0)
			{
				(*all)->bonus.col = 100;
				(*all)->bonus.life--;
				(*all)->bonus.loop2 = 0;
			}
		}
	}
}

void		manage_life(t_all **all, char c)
{
	win_life(all);
	lose_life(all, c);
	if ((*all)->bonus.loop2 > 3)
		(*all)->bonus.col = 0;
	if ((*all)->bonus.life == 0)
		draw_replay(all, &(*all)->bonus.dead, 3, 2);
}
