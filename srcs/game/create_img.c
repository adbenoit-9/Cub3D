/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 17:42:13 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/01 17:57:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_image(t_game **game)
{
	if ((*game)->img.ptr != NULL)
	{
		mlx_destroy_image((*game)->mlx, (*game)->img.ptr);
		(*game)->img.ptr = NULL;
	}
	(*game)->img.ptr = mlx_new_image((*game)->mlx, (*game)->r[X],
					(*game)->r[Y]);
	(*game)->img.bpp = 32;
	(*game)->img.size_line = (*game)->r[X] * 4;
	(*game)->img.endian = 0;
	(*game)->img.data = (int *)mlx_get_data_addr((*game)->img.ptr,
		&(*game)->img.bpp, &(*game)->img.size_line, &(*game)->img.endian);
	ft_move(game);
	(*game)->screen.x = 0;
	draw_wall(game);
	draw_sprite(game, &(*game)->sp);
}

int		create_window(t_game **game)
{
	create_image(game);
	mlx_put_image_to_window((*game)->mlx, (*game)->win,
		(*game)->img.ptr, 0, 0);
	return (NO_ERR);
}
