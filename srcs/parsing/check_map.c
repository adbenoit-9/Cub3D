/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:24:17 by adbenoit          #+#    #+#             */
/*   Updated: 2020/08/13 00:58:30 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_up(t_game **game, char **map, int i, int j)
{
	int size;
	int size1;

	size = ft_strlen(map[i]);
	size1 = 0;
	if (i < (*game)->map_size - 1)
		size1 = ft_strlen(map[i + 1]);
	if (j < size1 && map[i + 1][j] != HOLE && map[i + 1][j] != WALL)
		exit_error(game, NULL, MAP_ERR);
	if (j < size1 - 1 && map[i + 1][j + 1] != HOLE && map[i + 1][j + 1] != WALL)
		exit_error(game, NULL, MAP_ERR);
	if (j != 0 && j < size1 && map[i + 1][j - 1] != HOLE && map[i + 1][j - 1] != WALL)
		exit_error(game, NULL, MAP_ERR);
	if (j != 0 && j < size && map[i][j - 1] != HOLE && map[i][j - 1] != WALL)
		exit_error(game, NULL, MAP_ERR);
	if (j < size - 1 && map[i][j + 1] != HOLE && map[i][j + 1] != WALL)
		exit_error(game, NULL, MAP_ERR);
}

static void	check_down(t_game **game, char **map, int i, int j)
{
	int size;

	size = 0;
	if (i > 0)
		size = ft_strlen(map[i - 1]);
	if (j != 0 && j < size && map[i - 1][j - 1] != HOLE &&
	map[i - 1][j - 1] != WALL)
		exit_error(game, NULL, MAP_ERR);
	if (j < size && map[i - 1][j] != HOLE &&
	map[i - 1][j] != WALL)
		exit_error(game, NULL, MAP_ERR);
	if (j < size - 1 && map[i - 1][j + 1] != HOLE && map[i - 1][j + 1] != WALL)
		exit_error(game, NULL, MAP_ERR);
}

static void	check_border(t_game **game, int x, int y, int n)
{
	while (x < n && (*game)->map[y][x])
	{
		if ((*game)->map[y][x] != WALL && (*game)->map[y][x] != HOLE)
			exit_error(game, NULL, MAP_ERR);
		x++;
	}
}

static void	check_end(t_game **game, int size, int i, int j)
{
	if (i == size - 1)
	{
		if ((*game)->map[i][j] != WALL &&
		(*game)->map[i][j] != HOLE)
			exit_error(game, NULL, MAP_ERR);
	}
}

int			finish_parse_map(t_game **game)
{
	int i;
	int	j;
	int size[2];

	if ((*game)->player.start_pos != 1)
		exit_error(game, NULL, MAP_ERR);
	i = -1;
	while ((*game)->map[++i])
	{
		if (i > 0)
		{
			size[1] = ft_strlen((*game)->map[i]);
			size[0] = ft_strlen((*game)->map[i - 1]);
			check_border(game, size[0] - 1, i, size[1]);
			check_border(game, size[1] - 1, i - 1, size[0]);
		}
		j = -1;
		while ((*game)->map[i][++j])
		{
			if ((*game)->map[i][j] == HOLE)
			{
				check_up(game, (*game)->map, i, j);
				check_down(game, (*game)->map, i, j);
			}
			check_end(game, (*game)->map_size, i, j);
		}
	}
	return (NO_ERR);
}
