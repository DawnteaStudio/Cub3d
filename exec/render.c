/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:42:21 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/26 13:35:20 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_wall(t_play *play)
{
	int	i;
	int	j;
	int	height;

	i = 0;
	height = 0;
	while (i < play->win_h)
	{
		j = 0;
		while (j < play->win_w)
		{
			play->map.data[height] = play->screen[i][j];
			j++;
			height++;
		}
		i++;
	}
	mlx_put_image_to_window(play->mlx, play->win, play->map.image, 0, 0);
}

void	render_background(t_play *play)
{
	int	i;
	int	j;
	int	ceil;
	int	floor;

	ceil = play->map.ceiling[0] << 16 \
	| play->map.ceiling[1] << 8 | play->map.ceiling[2];
	floor = play->map.floor[0] << 16 \
	| play->map.floor[1] << 8 | play->map.floor[2];
	i = 0;
	while (i < play->win_h)
	{
		j = 0;
		while (j < play->win_w)
		{
			if (i < play->win_h / 2)
				play->screen[i][j] = ceil;
			else
				play->screen[i][j] = floor;
			j++;
		}
		i++;
	}
}
