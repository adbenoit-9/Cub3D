/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Adeline <Adeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:57:19 by adbenoit          #+#    #+#             */
/*   Updated: 2020/05/02 19:14:49 by Adeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    put_weapon(t_all **all)
{
	int i;

	(*all)->bonus.weap.bpp = 32;
	(*all)->bonus.weap.endian = 0;
	i = 0;
	while (i < 5)
	{
		add_dim_xpm(all, (*all)->bonus.path[i], &(*all)->bonus.weap.dim[i][X], &(*all)->bonus.weap.dim[i][Y]);
		(*all)->bonus.weap.size_line = (*all)->bonus.weap.dim[i][X] * 4;
		if (((*all)->bonus.weap.ptr = mlx_xpm_file_to_image((*all)->mlx, (*all)->bonus.path[i], &(*all)->bonus.weap.dim[i][X], &(*all)->bonus.weap.dim[i][Y])) == NULL)
			ft_error(all, NULL, FILE_ERR);
		(*all)->bonus.weap.data[i] = (int *)mlx_get_data_addr((*all)->bonus.weap.ptr, &(*all)->bonus.weap.bpp, &(*all)->bonus.weap.size_line, &(*all)->bonus.weap.endian);
		i++;
	}
}

void    print_weapon(t_all **all, int pull)
{
	int		start[2];
	int		end[2];
    int     pix[2];
    int     index[2];
    int     h;
    int     w;

    h = abs((int)((*all)->r[Y] / 3));
    w = abs((int)((*all)->r[Y] / 2));
    start[X] = (*all)->r[X] / 2 - w / 2;
    end[X] = start[X] + w;
    index[X] = 0;
    while (start[X] < end[X])
	{
        index[Y] = 0;
        pix[X] = index[X] * (*all)->bonus.weap.dim[pull][X] / w;
		start[Y] = (*all)->r[Y] - h;
        end[Y] = start[Y] + h;
		while (start[Y] < end[Y])
		{
            pix[Y] = index[Y] * (*all)->bonus.weap.dim[pull][Y] / h;
		    if ((*all)->bonus.weap.data[pull][(int)((*all)->bonus.weap.dim[pull][X] * pix[Y] + pix[X])] != -16777216)
			    (*all)->img.data[start[X] + (*all)->r[X] * start[Y]] = (*all)->bonus.weap.data[pull][(int)((*all)->bonus.weap.dim[pull][X] * pix[Y] + pix[X])];
		    start[Y]++;
            index[Y]++;
		}
        index[X]++;
		start[X]++;
    }
}