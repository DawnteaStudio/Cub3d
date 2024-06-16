/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:49:17 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/16 22:21:31 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray_setting(t_play *play, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)play->win_w - 1;
	play->ray.ray_x = play->ray.dir_x + play->ray.plane_x * camera_x;
	play->ray.ray_y = play->ray.dir_y + play->ray.plane_y * camera_x;
	play->map.start_x = (int)play->player.x;
	play->map.start_y = (int)play->player.y;
	if (play->ray.dir_x == 0)
		play->ray.delta_x = 1;
	else
		play->ray.delta_x = fabs(1 / play->ray.dir_x);
	if (play->ray.dir_y == 0)
		play->ray.delta_y = 1;
	else
		play->ray.delta_y = fabs(1 / play->ray.dir_y);
}
