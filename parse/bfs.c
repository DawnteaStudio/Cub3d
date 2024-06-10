/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:29:08 by erho              #+#    #+#             */
/*   Updated: 2024/06/04 16:30:08 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_range(int y, int x, t_map *m)
{
	if (y >= m->y_size || y < 0 || x >= (int)ft_strlen(m->field[y]) || x < 0)
		return (TRUE);
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
		m->start_x = x;
		m->start_y = y;
		return (TRUE);
	}
	return (FALSE);
}

void	visite(t_queue *queue, int y, int x, int **visited)
{
	q_push(queue, make_node(y, x));
	visited[y][x] = 1;
}

void	find_component(t_map *m, int start_y, int start_x, int **visited)
{
	t_search	search;

	set_search(&search);
	visite(search.queue, start_y, start_x, visited);
	while (search.queue->front != NULL)
	{
		search.idx = -1;
		while (++search.idx < 4)
		{
			search.y = search.queue->front->y + search.dy[search.idx];
			search.x = search.queue->front->x + search.dx[search.idx];
			if (find_next_idx(m, search.y, search.x, visited) == TRUE)
				visite(search.queue, search.y, search.x, visited);
		}
		q_pop(search.queue);
	}
	free_search(&search);
}

void	find_space(t_map *m, int start_y, int start_x, int **visited)
{
	t_search	search;

	set_search(&search);
	visite(search.queue, start_y, start_x, visited);
	while (search.queue->front != NULL)
	{
		search.idx = -1;
		while (++search.idx < 4)
		{
			search.y = search.queue->front->y + search.dy[search.idx];
			search.x = search.queue->front->x + search.dx[search.idx];
			if (check_range(search.y, search.x, m) == TRUE)
				search.is_outside = TRUE;
			else if (m->field[search.y][search.x] == ' '
				&& !visited[search.y][search.x])
				visite(search.queue, search.y, search.x, visited);
		}
		q_pop(search.queue);
	}
	if (search.is_outside == FALSE)
		print_error(ERROR_INVALID_MAP);
	free_search(&search);
}
