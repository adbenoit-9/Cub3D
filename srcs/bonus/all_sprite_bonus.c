/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_sprite_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Adeline <Adeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:10:15 by adbenoit          #+#    #+#             */
/*   Updated: 2020/05/12 12:35:13 by Adeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_all_sprite(t_sprite *sp)
{
	double tmp;
	int i;
	int j;

	j = 0;
	while (j < sp->count)
	{
		i = 0;
		while (i < sp->count - 1)
		{
			if (sp->dist[i] < sp->dist[i + 1])
			{
				tmp = sp->dist[i];
				sp->dist[i] = sp->dist[i + 1];
				sp->dist[i + 1] = tmp;
				tmp = sp->coor[i][X];
				sp->coor[i][X] = sp->coor[i + 1][X];
				sp->coor[i + 1][X] = tmp;
				tmp = sp->coor[i][Y];
				sp->coor[i][Y] = sp->coor[i + 1][Y];
				sp->coor[i + 1][Y] = tmp;
				tmp = sp->type[i];
				sp->type[i] = sp->type[i + 1];
				sp->type[i + 1] = tmp;
				tmp = sp->dead[i];
				sp->dead[i] = sp->dead[i + 1];
				sp->dead[i + 1] = tmp;
				tmp = sp->see[i];
				sp->see[i] = sp->see[i + 1];
				sp->see[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}

void	print_all_sprites(t_all **all, t_sprite *sp)
{
	int		i;

	i = 0;
	add_dist(all, sp, sort_all_sprite);
	(*all)->invdet = 1.0 / ((*all)->grid.plane[X] * (*all)->player.dir[Y] - (*all)->player.dir[X] * (*all)->grid.plane[Y]);
	while (i < sp->count)
	{
		if (sp->dead[i] == 0 && sp->type[i] == OBJ)
			raycast_sprite(all, sp, sp);
		else if (sp->dead[i] == 0 && sp->type[i] == OBJ1)
			raycast_sprite(all, sp, &(*all)->bonus.s1);
		else if (sp->dead[i] == 1 && sp->type[i] == OBJ1)
			raycast_sprite(all,  sp, &(*all)->bonus.sa);
		i++;
	}
}