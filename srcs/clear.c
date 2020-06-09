/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:56:05 by adbenoit          #+#    #+#             */
/*   Updated: 2020/06/08 15:37:01 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_sprites(t_game **game)
{
	free_tab_nb((void **)(*game)->sp.coor, (*game)->sp.count);
	free_tab_nb((void **)(*game)->sp.pos, (*game)->sp.count);
	free((*game)->sp.dead);
	free((*game)->sp.see);
	free((*game)->sp.dist);
	free((*game)->sp.type);
	if ((*game)->sp.img.ptr)
		mlx_destroy_image((*game)->mlx, (*game)->sp.img.ptr);
	if ((*game)->sp_foe.img.ptr)
		mlx_destroy_image((*game)->mlx, (*game)->sp_foe.img.ptr);
	if ((*game)->sp_dead.img.ptr)
		mlx_destroy_image((*game)->mlx, (*game)->sp_dead.img.ptr);
}

void	clear_textures(t_game **game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if ((*game)->text.ptr[i])
			mlx_destroy_image((*game)->mlx, (*game)->text.ptr[i]);
		if ((*game)->door.img.ptr[i])
			mlx_destroy_image((*game)->mlx, (*game)->door.img.ptr[i]);
		if ((*game)->weap.img.ptr[i])
			mlx_destroy_image((*game)->mlx, (*game)->weap.img.ptr[i]);
		i++;
	}
}

void	clear_bonus(t_game **game)
{
	if ((*game)->heart.ptr)
		mlx_destroy_image((*game)->mlx, (*game)->heart.ptr);
	if ((*game)->lose_game.ptr)
		mlx_destroy_image((*game)->mlx, (*game)->lose_game.ptr);
	if ((*game)->win_game.ptr)
		mlx_destroy_image((*game)->mlx, (*game)->win_game.ptr);
	free_tab_nb((void **)(*game)->path_bonus, NB_BON);
}

void	clear_utils(t_game **game)
{
	free_tab_char((*game)->map);
	free_tab_nb((void **)(*game)->path, 5);
	free((*game)->wall.dist);
	if ((*game)->img.ptr)
		mlx_destroy_image((*game)->mlx, (*game)->img.ptr);
	if ((*game)->win)
	{
		mlx_clear_window((*game)->mlx, (*game)->win);
		mlx_destroy_window((*game)->mlx, (*game)->win);
	}
	// system("leaks Cub3D");
}
