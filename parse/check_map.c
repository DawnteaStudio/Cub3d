/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:16:04 by erho              #+#    #+#             */
/*   Updated: 2024/06/02 22:13:42 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	find_target(char c, int isvisit)
{
	if (c == '0' && isvisit == 0)
		return (TRUE);
	else if ((c == 'N' || c == 'S' || c == 'W' || c == 'E') && isvisit == 0)
		return (TRUE);
	return (FALSE);
}

int	**set_visited(t_map *m)
{
	int		**res;
	size_t	idx;
	size_t	len;

	res = (int **)malloc(sizeof(int *) * (m->y_size + 1));
	if (res == NULL)
		ft_error(MEMORY);
	res[m->y_size] = NULL;
	idx = 0;
	while (idx < m->y_size)
	{
		len = ft_strlen(m->field[idx]);
		res[idx] = (int *)malloc(sizeof(int) * len);
		if (res[idx] == NULL)
			ft_error(MEMORY);
		ft_memset(res[idx], 0, sizeof(int) * len);
		idx++;
	}
	return (res);
}

void check_front_space(size_t *x, size_t y, t_map *m)
{
	while (*x < m->x_size && m->field[y][*x] == ' ')
		(*x)++;
	if (*x == m->x_size - 1)
		print_error(ERROR_INVALID_MAP);
}

void check_back_space(size_t *x, size_t y, t_map *m)
{
	while (*x < m->x_size && m->field[y][*x] == ' ')
		(*x)++;
	if (*x != m->x_size - 1)
		print_error(ERROR_INVALID_MAP);
}

void	is_valid_map(t_map *m)
{
	int		**visited;
	size_t	x;
	size_t	y;

	visited = set_visited(m);
	y = 0;
	while (y < m->y_size)
	{
		m->x_size = ft_strlen(m->field[y]);
		x = 0;
		check_front_space(&x, y, m);
		while (x < m->x_size && m->field[y][x] != ' ')
		{
			if (find_target(m->field[y][x], visited[y][x]) == TRUE)
				bfs(m, y, x, visited);
			x++;
		}
		check_back_space(&x, y, m);
		y++;
	}
	free_exp(visited);
}
