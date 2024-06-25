/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:23:35 by erho              #+#    #+#             */
/*   Updated: 2024/06/26 01:23:37 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	check_range(int y, int x, t_map *m)
{
	if (y >= m->y_size || y < 0 || x >= m->x_size || x < 0)
		return (TRUE);
	return (FALSE);
}

int check_door(t_map *m, int y, int x, int **visited)
{
	if (m->field[y][x] == 'D' && !visited[y][x])
	{
		if (!check_range(y - 1, x, m) && !check_range(y + 1, x, m))
		{
			if (m->field[y - 1][x] == '1' && m->field[y + 1][x] == '1')
				return (TRUE);
		}
		if (!check_range(y, x - 1, m) && !check_range(y, x + 1, m))
		{
			if (m->field[y][x - 1] == '1' && m->field[y][x + 1] == '1')
				return (TRUE);
		}
		print_error(ERROR_INVALID_MAP);
	}
	return (FALSE);
}

int	find_next_idx(t_map *m, int y, int x, int **visited)
{
	if (check_range(y, x, m) == TRUE)
		print_error(ERROR_INVALID_MAP);
	if (m->field[y][x] == ' ' || m->field[y][x] == '\0')
		print_error(ERROR_INVALID_MAP);
	if (m->field[y][x] == '0' && !visited[y][x])
		return (TRUE);
	if ((m->field[y][x] == 'N' || m->field[y][x] == 'S' || m->field[y][x] == 'W'
		 || m->field[y][x] == 'E') && !visited[y][x])
	{
		if (m->start_x != -1)
			print_error(ERROR_INVALID_MAP);
		if (m->field[y][x] == 'N')
			m->direction = NORTH;
		else if (m->field[y][x] == 'S')
			m->direction = SOUTH;
		else if (m->field[y][x] == 'W')
			m->direction = WEST;
		else
			m->direction = EAST;
		m->start_x = x;
		m->start_y = y;
		return (TRUE);
	}
	return (check_door(m, y, x, visited));
}

void	visit(t_queue *queue, int y, int x, int **visited)
{
	q_push(queue, make_node(y, x));
	visited[y][x] = 1;
}
