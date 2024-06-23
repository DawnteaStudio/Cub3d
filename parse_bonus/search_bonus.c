/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:08:55 by erho              #+#    #+#             */
/*   Updated: 2024/06/23 15:00:01 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	free_search(t_search *search)
{
	free(search->dy);
	free(search->dx);
	free(search->queue);
}

void	set_search(t_search *search)
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
