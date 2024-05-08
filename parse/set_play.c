/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_play.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:43:32 by erho              #+#    #+#             */
/*   Updated: 2024/05/09 05:30:04 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initial_play(t_play *play)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		play->images[i].path = NULL;
		i++;
	}
	ft_memset(&play->map.ceiling, -1, sizeof(int *));
	ft_memset(&play->map.floor, -1, sizeof(int *));
}
