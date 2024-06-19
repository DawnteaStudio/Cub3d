/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:49:17 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/19 22:44:17 by sewopark         ###   ########.fr       */
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
		play->ray.delta_x = 1.1;
	else
		play->ray.delta_x = fabs(1 / play->ray.dir_x);
	if (play->ray.dir_y == 0)
		play->ray.delta_y = 1.1;
	else
		play->ray.delta_y = fabs(1 / play->ray.dir_y);
}

void	calc_size_dist_ray(t_play *play)
{
	t_ray	*tmp;

	tmp = &play->ray;
	if (tmp->dir_x < 0)
	{
		play->player.step_x = -1;
		tmp->size_x = (play->player.x - play->map.start_x) * tmp->delta_x;
	}
	else
	{
		play->player.step_x = 1;
		tmp->size_x = (play->map.start_x + 1.0 - play->player.x) * tmp->delta_x;
	}
	if (tmp->dir_y < 0)
	{
		play->player.step_y = -1;
		tmp->size_y = (play->player.y - play->map.start_y) * tmp->delta_y;
	}
	else
	{
		play->player.step_y = 1;
		tmp->size_y = (play->map.start_y + 1.0 - play->player.y) * tmp->delta_y;
	}
}

void	calc_ray_hit(t_play *play)
{
	while (TRUE)
	{
		if (play->ray.size_x < play->ray.size_y)
		{
			play->ray.size_x += play->ray.delta_x;
			play->map.start_x += play->player.step_x;
			play->ray.wall = WALL_X;
		}
		else
		{
			play->ray.size_y += play->ray.delta_y;
			play->map.start_y += play->player.step_y;
			play->ray.wall = WALL_Y;
		}
		if (play->map.field[play->map.start_x][play->map.start_y] == '1')
			break ;
	}
	if (play->ray.wall == WALL_X)
		play->ray.wall_dist = (play->map.start_x - play->player.x + \
		(1 - play->player.step_x) / 2) / play->ray.ray_x;
	else
		play->ray.wall_dist = (play->map.start_y - play->player.y + \
		(1 - play->player.step_y) / 2) / play->ray.ray_y;
}

void	calc_draw_height(t_play *play)
{
	play->player.line_h = (int)(play->win_h / play->ray.wall_dist);
	play->player.draw_start = play->win_h / 2 - play->player.line_h / 2;
	if (play->player.draw_start < 0)
		play->player.draw_start = 0;
	play->player.draw_end = play->win_h / 2 + play->player.line_h / 2;
	if (play->player.draw_end >= play->win_h)
		play->player.draw_end = play->win_h - 1;
	if ()
}