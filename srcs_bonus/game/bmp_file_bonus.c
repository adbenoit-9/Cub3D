/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_file_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:27:44 by adbenoit          #+#    #+#             */
/*   Updated: 2020/07/05 20:17:14 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	set_bmp(t_game **game, unsigned char **head)
{
	int x;
	int y;

	x = (*game)->r[X];
	y = (*game)->r[Y];
	ft_bzero(*head, 54);
	(*head)[0] = 'B';
	(*head)[1] = 'M';
	(*head)[2] = (unsigned char)(54 + 4 * x * y);
	(*head)[3] = (unsigned char)((54 + 4 * x * y) >> 8);
	(*head)[4] = (unsigned char)((54 + 4 * x * y) >> 16);
	(*head)[5] = (unsigned char)((54 + 4 * x * y) >> 24);
	(*head)[10] = 54;
	(*head)[14] = 40;
	(*head)[18] = (unsigned char)x;
	(*head)[19] = (unsigned char)(x >> 8);
	(*head)[20] = (unsigned char)(x >> 16);
	(*head)[21] = (unsigned char)(x >> 24);
	(*head)[22] = (unsigned char)y;
	(*head)[23] = (unsigned char)(y >> 8);
	(*head)[24] = (unsigned char)(y >> 16);
	(*head)[25] = (unsigned char)(y >> 24);
	(*head)[26] = 1;
	(*head)[28] = 32;
}

void		save_bmp(t_game **game)
{
	int				fd;
	int				index[2];
	unsigned char	*head;
	int				*pixel;
	int				k;

	if (!(head = malloc(sizeof(char) * 54)))
		exit_error(game, NULL, MAL_ERR);
	set_bmp(game, &head);
	fd = open("cub3d.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	write(fd, head, 54);
	free(head);
	if (!(pixel = malloc(sizeof(int) * (*game)->r[Y] * (*game)->r[X])))
		exit_error(game, NULL, MAL_ERR);
	index[X] = (*game)->r[Y];
	k = -1;
	while (--index[X] >= 0)
	{
		index[Y] = -1;
		while (++index[Y] < (*game)->r[X])
			pixel[++k] = (*game)->img.data[index[Y] + (*game)->r[X] * index[X]];
	}
	write(fd, pixel, (*game)->r[X] * (*game)->r[Y] * 4);
	free(pixel);
	close(fd);
}
