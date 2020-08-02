/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:46:47 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/02 23:57:29 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_sprite_pix(t_game **game, t_sprite *sp, t_img *s_im, int *end)
{
	int	px[2];
	int	s[2];

	s[X] = sp->screen - sp->w / 2 - 1;
	if (s[X] < 0)
		s[X] = -1;
	while (++s[X] < end[X])
	{
		px[X] = (int)(256 * (s[X] - (sp->screen - sp->w / 2)) *
					s_im->dim[X] / sp->w) / 256;
		s[Y] = (*game)->r[Y] / 2 - sp->h / 2 - 1;
		if (s[Y] < -1)
			s[Y] = -1;
		while (++s[Y] < end[Y] && sp->transf[Y] > 0 && s[X] > 0 && s[X]
				< (*game)->r[X] && sp->transf[Y] < (*game)->wall.dist[s[X]])
		{
			if (sp->see)
				sp->see[sp->index] = TRUE;
			px[Y] = (((s[Y] * 256 - (*game)->r[Y] * 128 + sp->h * 128) *
						s_im->dim[Y]) / sp->h) / 256;
			if (s_im->data[(int)(s_im->dim[X] * px[Y] + px[X])] != -16777216)
				(*game)->img.data[s[X] + (*game)->r[X] * s[Y]] = s_im->data[
					(int)(s_im->dim[X] * px[Y] + px[X])] + (*game)->hit;
		}
	}
}

void		raycast_sprite(t_game **game, t_sprite *sp, t_img *sp_img)
{
	int		end[2];
	int		i;

	i = sp->index;
	sp->pos[i][X] = sp->coor[i][X] - (*game)->player.pos[X];
	sp->pos[i][Y] = sp->coor[i][Y] - (*game)->player.pos[Y];
	sp->transf[X] = (*game)->invdet * ((*game)->player.dir[Y] * sp->pos[i][X] -
					(*game)->player.dir[X] * sp->pos[i][Y]);
	sp->transf[Y] = (*game)->invdet * ((*game)->screen.plane[X] * sp->pos[i][Y]
					- (*game)->screen.plane[Y] * sp->pos[i][X]);
	sp->h = abs((int)((*game)->r[Y] / sp->transf[Y]));
	sp->w = abs((int)((*game)->r[Y] / sp->transf[Y]));
	sp->screen = (int)(((*game)->r[X] / 2) *
				(1 + sp->transf[X] / sp->transf[Y]));
	end[Y] = sp->h / 2 + (*game)->r[Y] / 2;
	if (end[Y] >= (*game)->r[Y])
		end[Y] = (*game)->r[Y] - 1;
	end[X] = sp->w / 2 + sp->screen;
	if (end[X] >= (*game)->r[X])
		end[X] = (*game)->r[X] - 1;
	draw_sprite_pix(game, sp, sp_img, end);
}
