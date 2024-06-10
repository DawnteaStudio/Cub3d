/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:43:32 by erho              #+#    #+#             */
/*   Updated: 2024/06/04 16:30:57 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_height(t_play *play)
{
	int	i;
	int	width;

	i = play->height - 1;
	while (i >= 0)
	{
		width = 0;
		while (play->origin[i][width] == ' ')
			width++;
		if (play->origin[i][width] != '\0')
		{
			play->height = i + 1;
			break ;
		}
		i--;
	}
}

void	initial_play(t_play *play)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		play->images[i].path = NULL;
		i++;
	}
	play->check_parsing = FALSE;
	play->height = 0;
	play->map.start_x = -1;
	play->map.start_y = -1;
	ft_memset(&play->map.ceiling, -1, sizeof(int *));
	ft_memset(&play->map.floor, -1, sizeof(int *));
}
