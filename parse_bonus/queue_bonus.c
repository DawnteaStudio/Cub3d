/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:28:00 by erho              #+#    #+#             */
/*   Updated: 2024/06/23 14:59:54 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_queue	*make_queue(void)
{
	t_queue	*q;

	q = (t_queue *)malloc(sizeof(t_queue));
	if (q == NULL)
		ft_error(MEMORY);
	q->front = NULL;
	q->back = NULL;
	return (q);
}

t_node	*make_node(int y, int x)
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
	if (q->front == NULL)
	{
		q->front = node;
		q->back = node;
	}
	else
	{
		q->back->next = node;
		q->back = node;
	}
}

void	q_pop(t_queue *q)
{
	t_node	*delete_node;

	delete_node = q->front;
	if (delete_node == NULL)
		return ;
	if (q->front != q->back)
		q->front = q->front->next;
	else
	{
		q->front = NULL;
		q->back = NULL;
	}
	free(delete_node);
}
