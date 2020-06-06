/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_sprite_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 21:16:20 by adbenoit          #+#    #+#             */
/*   Updated: 2020/06/06 22:44:28 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	switch_sprite(t_sprite *sp, int i)
{
	double	tmp;

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

static void	sort_all_sprite(t_sprite *sp)
{
	int i;
	int j;

	j = 0;
	while (j < sp->count)
	{
		i = 0;
		while (i < sp->count - 1)
		{
			if (sp->dist[i] < sp->dist[i + 1])
				switch_sprite(sp, i);
			i++;
		}
		j++;
	}
}

void		set_sprite_coor(t_all **all, char *line, int i)
{
	int	size;

	if (line[i] == OBJ || line[i] == OBJ1)
	{
		(*all)->sp.count++;
		size = (*all)->sp.count;
		if (!((*all)->sp.coor = realloc_doub((*all)->sp.coor, size)))
			exit_error(all, line, MAL_ERR);
		if (!((*all)->sp.type = realloc((*all)->sp.type, size + 1)))
			exit_error(all, NULL, MAL_ERR);
		(*all)->sp.coor[size - 1][X] = i + 0.5;
		(*all)->sp.coor[size - 1][Y] = (*all)->map_size - 1 + 0.5;
		(*all)->sp.type[size - 1] = line[i];
		if (line[i] == OBJ1)
			(*all)->bonus.foe++;
		(*all)->sp.type[size] = 0;
	}
}

void		draw_all_sprites(t_all **all, t_sprite *sp)
{
	int		i;

	i = 0;
	add_dist(all, sp, sort_all_sprite);
	(*all)->invdet = 1.0 / ((*all)->screen.plane[X] * (*all)->player.dir[Y] -
	(*all)->player.dir[X] * (*all)->screen.plane[Y]);
	while (i < sp->count)
	{
		sp->index = i;
		if (sp->dead[i] == FALSE && sp->type[i] == OBJ)
			raycast_sprite(all, sp, &sp->img);
		else if (sp->dead[i] == FALSE && sp->type[i] == OBJ1)
			raycast_sprite(all, sp, &(*all)->bonus.s1.img);
		else if (sp->dead[i] == TRUE && sp->type[i] == OBJ1)
			raycast_sprite(all, sp, &(*all)->bonus.sa.img);
		i++;
	}
}
