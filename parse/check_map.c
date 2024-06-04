/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:16:04 by erho              #+#    #+#             */
/*   Updated: 2024/06/04 16:00:58 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	find_target(int y, int x, char **visited, t_map *m)
{
	char	c;

	c = m->field[y][x];
	if (c == '1' || visited[y][x] == '1')
		return ;
	if (c == '0' || (c == 'N' || c == 'S' || c == 'W' || c == 'E'))
		find_component(m, y, x, visited);
	else if (c == ' ')
		find_space(m, y, x, visited);
	else
		print_error(ERROR_INVALID_MAP);
}

char	**set_visited(t_map *m)
{
	char	**res;
	int		idx;
	int		len;

	res = (char **)malloc(sizeof(char *) * (m->y_size + 1));
	if (res == NULL)
		ft_error(MEMORY);
	res[m->y_size] = NULL;
	idx = 0;
	while (idx < m->y_size)
	{
		len = ft_strlen(m->field[idx]);
		res[idx] = (char *)malloc(sizeof(char) * (len + 1));
		if (res[idx] == NULL)
			ft_error(MEMORY);
		res[idx][len] = '\0';
		ft_memset(res[idx], '0', sizeof(char) * len);
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

void	check_component(t_map *m, char **visited)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->y_size)
	{
		m->x_size = (int)ft_strlen(m->field[y]);
		printf("visited: %s\n", visited[y]);
		x = 0;
		while (x < m->x_size)
		{
			while (m->field[y][x] == ' ')
				x++;
//			if (x != m->y_size && m->field[y][x] == '1' && visited[y][x] == '0')
//				print_error(ERROR_INVALID_MAP);
			x++;
		}
		y++;
	}
	free_exp(visited);
}

void	is_valid_map(int *idx, t_map *m)
{
	char	**visited;
	int		x;
	int		y;

	visited = set_visited(m);
	y = 0;
	while (y < m->y_size)
	{
		m->x_size = (int)ft_strlen(m->field[y]);
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
	free_exp(visited);
	//check_component(m, visited);
}
