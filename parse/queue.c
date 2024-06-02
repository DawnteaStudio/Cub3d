/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:28:00 by erho              #+#    #+#             */
/*   Updated: 2024/05/21 20:11:31 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_queue	*make_queue(void)
{
	t_queue *q;

	q = (t_queue *)malloc(sizeof(t_queue));
	if (q == NULL)
		ft_error(MEMORY);
	q->front = NULL;
	q->back = NULL;
	return (q);
}

t_node	*make_node(size_t y, size_t x)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		ft_error(MEMORY);
	node->y = y;
	node->x = x;
	node->next = NULL;
	return (node);
}

void	q_push(t_queue *q, t_node *node)
{
	t_node	*temp;

	if (q->front == NULL)
	{
		q->front = node;
		q->back = node;
	}
	else
	{
		node->next = q->front;
		q->front = node;
	}
}

void	q_pop(t_queue *q)
{
	t_node	*delete_node;
	t_node	*temp;

	delete_node = q->back;
	if (delete_node == NULL)
		return ;
	if (q->front != q->back)
	{
		temp = q->front;
		while (temp->next != q->back)
			temp = temp->next;
		temp->next = NULL;
		q->back = temp;
	}
	else
	{
		q->front = NULL;
		q->back = NULL;
	}
	free(delete_node);
}
