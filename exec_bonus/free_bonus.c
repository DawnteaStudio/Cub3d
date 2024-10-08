/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:26:25 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/26 20:00:39 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	exit_game(t_play *play)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(play->images[i].image);
		i++;
	}
	i = 0;
	while (i < play->win_h)
	{
		free(play->screen[i]);
		i++;
	}
	free(play->screen);
	if (play && play->map.image)
		mlx_destroy_image(play->mlx, play->map.image);
	if (play->win)
		mlx_destroy_window(play->mlx, play->win);
	free(play->door.close);
	exit(0);
	return (0);
}
