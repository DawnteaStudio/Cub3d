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

void	set_dy_dx(int **dy, int **dx)
{
	*dy = (int *)malloc(sizeof(int) * 4);
	*dx = (int *)malloc(sizeof(int) * 4);
	if (*dy == NULL || *dx == NULL)
		ft_error(MEMORY);
	(*dy)[0] = 0;
	(*dy)[1] = -1;
	(*dy)[2] = 0;
	(*dy)[3] = 1;
	(*dx)[0] = -1;
	(*dx)[1] = 0;
	(*dx)[2] = 1;
	(*dx)[3] = 0;
}

int	find_next_idx(t_map *m, size_t y, size_t x, int **visited)
{
	if (y >= m->y_size || y < 0 || x >= ft_strlen(m->field[y]) || x < 0)
		print_error(ERROR_INVALID_MAP);
	if (m->field[y][x] == ' ' || m->field[y][x] == '\0')
		print_error(ERROR_INVALID_MAP);
	if (m->field[y][x] == '1' || (m->field[y][x] == '0' && visited[y][x] == 1))
		return (FALSE);
	if (m->field[y][x] == 'N' || m->field[y][x] == 'S'
		|| m->field[y][x] == 'W' || m->field[y][x] == 'E')
	{
		if (m->start_x != -1)
			print_error(ERROR_INVALID_MAP);
		m->start_x = x;
		m->start_y = y;
	}
	return (TRUE);
}

void	bfs(t_map *m, size_t start_y, size_t start_x, int **visited)
{
	t_queue	*queue;
	int		*dy;
	int		*dx;
	int		i;

	queue = make_queue();
	q_push(queue, make_node(start_y, start_x));
	visited[start_y][start_x] = 1;
	set_dy_dx(&dy, &dx);
	while (queue->front != NULL)
	{
		i = 0;
		while (i < 4)
		{
			if (find_next_idx(m, queue->front->y + dy[i],
				queue->front->x + dx[i], visited) == TRUE)
			{
				visited[queue->front->y + dy[i]][queue->front->x + dx[i]] = 1;
				q_push(queue, make_node(queue->front->y + dy[i],
					queue->front->x + dx[i]));
			}
			i++;
		}
		q_pop(queue);
	}
}
