/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:29:08 by erho              #+#    #+#             */
/*   Updated: 2024/06/02 21:44:36 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_range(int y, int x, t_map *m)
{
	if (y >= m->y_size || y < 0 || x >= (int)ft_strlen(m->field[y]) || x < 0)
		return (TRUE);
	return (FALSE);
}

int	find_next_idx(t_map *m, int y, int x, char **visited)
{

	if (check_range(y, x, m) == TRUE)
		print_error(ERROR_INVALID_MAP);
	if (m->field[y][x] == ' ' || m->field[y][x] == '\0')
		print_error(ERROR_INVALID_MAP);
	if (m->field[y][x] == '0' && visited[y][x] == '0')
		return (TRUE);
	if ((m->field[y][x] == 'N' || m->field[y][x] == 'S'
		|| m->field[y][x] == 'W' || m->field[y][x] == 'E') && visited[y][x] == '0')
	{
		if (m->start_x != -1)
			print_error(ERROR_INVALID_MAP);
		m->start_x = x;
		m->start_y = y;
		return (TRUE);
	}
	return (FALSE);
}

void set_search(t_search *search)
{
	search->queue = make_queue();
	search->is_outside = FALSE;
	search->dy = (int *)malloc(sizeof(int) * 4);
	search->dx = (int *)malloc(sizeof(int) * 4);
	if (search->dy == NULL || search->dx == NULL)
		ft_error(MEMORY);
	search->dy[0] = 0;
	search->dy[1] = -1;
	search->dy[2] = 0;
	search->dy[3] = 1;
	search->dx[0] = -1;
	search->dx[1] = 0;
	search->dx[2] = 1;
	search->dx[3] = 0;
}

void	find_component(t_map *m, int start_y, int start_x, char **visited)
{
	t_search	search;

	set_search(&search);
	q_push(search.queue, make_node(start_y, start_x));
	visited[start_y][start_x] = '1';
	while (search.queue->front != NULL)
	{
		search.idx = -1;
		while (++search.idx < 4)
		{
			search.y = search.queue->front->y + search.dy[search.idx];
			search.x = search.queue->front->x + search.dx[search.idx];
			if (find_next_idx(m, search.y, search.x, visited) == TRUE)
			{
				visited[search.y][search.x] = '1';
				q_push(search.queue, make_node(search.y, search.x));
			}
		}
		q_pop(search.queue);
	}
	free(search.dy);
	free(search.dx);
	free(search.queue);
}

void	find_space(t_map *m, int start_y, int start_x, char **visited)
{
	t_search	search;

	set_search(&search);
	q_push(search.queue, make_node(start_y, start_x));
	visited[start_y][start_x] = '1';
	while (search.queue->front != NULL)
	{
		search.idx = -1;
		while (++search.idx < 4)
		{
			search.y = search.queue->front->y + search.dy[search.idx];
			search.x = search.queue->front->x + search.dx[search.idx];
			if (check_range(search.y, search.x, m) == TRUE)
				search.is_outside = TRUE;
			else if (m->field[search.y][search.x] == ' ' && visited[search.y][search.x] == '0')
			{
				visited[search.y][search.x] = '1';
				q_push(search.queue, make_node(search.y, search.x));
			}
		}
		q_pop(search.queue);
	}
	if (search.is_outside == FALSE)
		print_error(ERROR_INVALID_MAP);
	free(search.dy);
	free(search.dx);
	free(search.queue);
}
