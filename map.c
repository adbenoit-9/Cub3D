/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:42:10 by adbenoit          #+#    #+#             */
/*   Updated: 2020/03/05 15:30:31 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_map(char *line, t_all **all)
{
	int i;

	i = 0;
	if (!((*all)->map[(*all)->i_map] = malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (ft_error(all, line, PARS_ERR));
	while (line[i])
	{
		if (line[i] == OBJ)
		{
			(*all)->sp.count++;
			if (!((*all)->sp.coor = realloc_doub((*all)->sp.coor, (*all)->sp.count)))
				return (ft_error(all, line, PARS_ERR));
			(*all)->sp.coor[(*all)->sp.count - 1][X] = i + 0.5;
			(*all)->sp.coor[(*all)->sp.count - 1][Y] = (*all)->i_map + 0.5;
		}
		(*all)->map[(*all)->i_map][i] = line[i];
		i++;
	}
	(*all)->map[(*all)->i_map][i] = 0;
	((*all)->i_map)++;
	return (ft_parsing(all));
}

int	add_info(char *line, t_all **all, int i)
{
	int j;
	int k;

	j = 0; 
	if (!((*all)->info[i] = malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (ft_error(all, line, PARS_ERR));
	while (line[j])
	{
		(*all)->info[i][j] = line[j];
		j++;
	}
	(*all)->info[i][j] = 0;
	return (ft_parsing(all));
}

int	map(char *line, t_all **all)
{
	static char str_char[NB_CHAR] = {WALL, OBJ, EMPT, HOLE, NORTH, SOUTH, EAST, WEST};
	int			i;
	int			j;
	int			size;

	j = 0;
	if ((line = ft_trim(line, ' ')) == NULL)
		return (ft_error(all, line, PARS_ERR));
	size = ft_strlen(line);
	if ((line[0] != WALL && line[0] != HOLE) || (size > 0 && line[size - 1] != WALL && line[size - 1] != HOLE))
		return (ft_error(all, line, PARS_ERR));
	while (line[j])
	{
		if ((*all)->i_map == 0 && line[j] != WALL && line[j] != HOLE)
			return (ft_error(all, line, PARS_ERR));
		i = 0;
		while (i < NB_CHAR && line[j] != str_char[i])
			i++;
		if (i > 3 && i < NB_CHAR)
		{
			(*all)->player.map[X] = j + 0.5;
			(*all)->player.map[Y] = (*all)->i_map;
			(*all)->player.o = line[j];
			(*all)->pos++;
		}
		if (i == NB_CHAR)
			return (ft_error(all, line, PARS_ERR));
		j++;
	}
	if (map_error(all, line) != NO_ERR)
		return (0);
	(*all)->map[(*all)->i_map] = 0;
	return (add_map(line, all));
}

int	info(char *line, t_all **all)
{
	static char *str_info[NB_INFO] = {INF_EA, INF_SO, INF_WE, INF_NO, INF_S, INF_R, INF_F, INF_C};
	int			i;
	int			size;

	i = 0;
	while (i < NB_INFO)
	{
		size = i < 4 ? 2 : 1;
		if (ft_strncmp(str_info[i], line, size) == 1 && (*all)->info[i] == 0)
		{
			line = ft_strtrim(line, " ", size);
			if (i < 5)
				return (add_info(line, all, i));
			else if (i == 5)
				return (add_r(all, line));
			else
				return (add_col(all, line, i));
		}
		i++;
	}
	(*all)->err = END_INFO;
	i = 0;
	while (i < NB_INFO - 3)
	{
		if ((*all)->info[i] == NULL)
			return (ft_error(all, line, PARS_ERR));
		i++;
	}
	(*all)->state = MAP;
	return (map(line, all));
}
