/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 17:43:24 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/13 00:10:11 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	screen_resize(t_game **game)
{
	int	x_max;
	int	y_max;

	mlx_mscreen_resolution(&x_max, &y_max);
	if ((*game)->r[X] > x_max)
		(*game)->r[X] = x_max;
	if ((*game)->r[Y] > y_max)
		(*game)->r[Y] = y_max;
}

void		start_game(t_game **game)
{
	if (!((*game)->mlx = mlx_init()))
		exit_error(game, NULL, MLX_ERR);
	screen_resize(game);
	finish_init(game, &(*game)->sp);
	init_player_dir(game, (*game)->player.start_o);
	load_tab_of_image(game, &(*game)->text, (*game)->path, 0);
	load_image(game, &(*game)->sp.img, (*game)->path[S]);
	if ((*game)->save == TRUE)
		save_bmp(game);
	if (!((*game)->win = mlx_new_window((*game)->mlx,
	(*game)->r[X], (*game)->r[Y], "Cub3D")))
		exit_error(game, NULL, MLX_ERR);
}
