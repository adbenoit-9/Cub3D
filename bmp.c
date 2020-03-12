/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:27:44 by adbenoit          #+#    #+#             */
/*   Updated: 2020/03/11 18:45:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_info_bmp(t_all ** all, unsigned char **head)
{
	if (!((*head) = malloc(sizeof(char) * 54)))
		exit(EXIT_FAILURE);
	ft_bzero(*head, 54);
	(*head)[0] = 'B';
	(*head)[1] = 'M';
	(*head)[2] = (unsigned char)(54 + 4 * (*all)->r[X] * (*all)->r[Y]);
	(*head)[3] = (unsigned char)((54 + 4 * (*all)->r[X] * (*all)->r[Y]) >> 8);
	(*head)[4] = (unsigned char)((54 + 4 * (*all)->r[X] * (*all)->r[Y]) >> 16);
	(*head)[5] = (unsigned char)((54 + 4 * (*all)->r[X] * (*all)->r[Y]) >> 24);
	(*head)[10] = 54;
	(*head)[14] = 40;
	(*head)[18] = (unsigned char)(((*all)->r[X]));
	(*head)[19] = (unsigned char)(((*all)->r[X]) >> 8);
	(*head)[20] = (unsigned char)(((*all)->r[X]) >> 16);
	(*head)[21] = (unsigned char)(((*all)->r[X]) >> 24);
	(*head)[22] = (unsigned char)(((*all)->r[Y]));
	(*head)[23] = (unsigned char)(((*all)->r[Y]) >> 8);
	(*head)[24] = (unsigned char)(((*all)->r[Y]) >> 16);
	(*head)[25] = (unsigned char)(((*all)->r[Y]) >> 24);
	(*head)[26] = 1;
	(*head)[28] = 32;
}

void	save_bmp(t_all **all)
{
	int	fd;
	int i;
	unsigned char  *head;
	int j;
	int *pixel;
	int k;

	add_info_bmp(all, &head);
	fd = open("cub3d.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	write(fd, head, 54);
	free(head);
	if (!(pixel = malloc(sizeof(int) * (*all)->r[Y] * (*all)->r[X])))
		exit(EXIT_FAILURE);
	i = (*all)->r[Y] - 1;
	k = 0;
	while (i >= 0)
	{
		j = 0;
		while (j < (*all)->r[X])
		{
			pixel[k] = (*all)->img.data[j + (*all)->r[X] * i];
			k++;
			j++;
		}
		i--;
	}
	write(fd, pixel, (*all)->r[X] * (*all)->r[Y] * 4);
	free(pixel);
	close(fd);
}