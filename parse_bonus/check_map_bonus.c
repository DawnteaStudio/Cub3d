/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:16:04 by erho              #+#    #+#             */
/*   Updated: 2024/06/23 14:59:38 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	find_target(int y, int x, int **visited, t_map *m)
{
	char	c;

	c = m->field[y][x];
	if (c == '1' || visited[y][x])
		return ;
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'D')
		find_component(m, y, x, visited);
	else if (c == ' ')
		find_space(m, y, x, visited);
	else
		print_error(ERROR_INVALID_MAP);
}

void	free_visited(int **visited)
{
	int	idx;

	idx = 0;
	while (visited[idx] != NULL)
	{
		free(visited[idx]);
		idx++;
	}
	free(visited);
}

int	**set_visited(t_map *m)
{
	int	**res;
	int	idx;

	res = (int **)malloc(sizeof(int *) * (m->y_size + 1));
	if (res == NULL)
		ft_error(MEMORY);
	res[m->y_size] = NULL;
	idx = 0;
	while (idx < m->y_size)
	{
		res[idx] = (int *)malloc(sizeof(int) * (m->x_size));
		if (res[idx] == NULL)
			ft_error(MEMORY);
		ft_memset(res[idx], 0, sizeof(int) * m->x_size);
		idx++;
	}
	return (res);
}

void	check_front_space(int *x, int y, t_map *m)
{
	while (m->field[y][*x] == ' ')
		(*x)++;
	if (*x == m->x_size)
		print_error(ERROR_INVALID_MAP);
}

void	is_valid_map(int *idx, t_map *m)
{
	int	**visited;
	int	x;
	int	y;

	visited = set_visited(m);
	y = 0;
	while (y < m->y_size)
	{
		x = 0;
		check_front_space(&x, y, m);
		while (x < m->x_size)
		{
			find_target(y, x, visited, m);
			x++;
		}
		y++;
	}
	if (m->start_x == -1)
		print_error(ERROR_INVALID_MAP);
	*idx += y - 1;
	free_visited(visited);
}
