/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:29:08 by erho              #+#    #+#             */
/*   Updated: 2024/06/26 01:24:15 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	find_component(t_map *m, int start_y, int start_x, int **visited)
{
	t_search	search;

	set_search(&search);
	find_next_idx(m, start_y, start_x, visited);
	visit(search.queue, start_y, start_x, visited);
	while (search.queue->front != NULL)
	{
		search.idx = -1;
		while (++search.idx < 4)
		{
			search.y = search.queue->front->y + search.dy[search.idx];
			search.x = search.queue->front->x + search.dx[search.idx];
			if (find_next_idx(m, search.y, search.x, visited) == TRUE)
				visit(search.queue, search.y, search.x, visited);
		}
		q_pop(search.queue);
	}
	free_search(&search);
}

void	find_space(t_map *m, int start_y, int start_x, int **visited)
{
	t_search	search;

	set_search(&search);
	visit(search.queue, start_y, start_x, visited);
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
				visit(search.queue, search.y, search.x, visited);
		}
		q_pop(search.queue);
	}
	if (search.is_outside == FALSE)
		print_error(ERROR_INVALID_MAP);
	free_search(&search);
}
