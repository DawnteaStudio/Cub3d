/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:01:23 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/26 20:33:02 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	event_left(t_play *play)
{
	double	speed;
	double	old_dir_x;
	double	old_plane_x;

	speed = -play->player.turn_speed;
	old_dir_x = play->ray.dir_x;
	old_plane_x = play->ray.plane_x;
	play->ray.dir_x = \
	old_dir_x * cos(speed) - play->ray.dir_y * sin(speed);
	play->ray.dir_y = \
	old_dir_x * sin(speed) + play->ray.dir_y * cos(speed);
	play->ray.plane_x = \
	old_plane_x * cos(speed) - play->ray.plane_y * sin(speed);
	play->ray.plane_y = \
	old_plane_x * sin(speed) + play->ray.plane_y * cos(speed);
}

void	event_right(t_play *play)
{
	double	speed;
	double	old_dir_x;
	double	old_plane_x;

	speed = play->player.turn_speed;
	old_dir_x = play->ray.dir_x;
	old_plane_x = play->ray.plane_x;
	play->ray.dir_x = \
	old_dir_x * cos(speed) - play->ray.dir_y * sin(speed);
	play->ray.dir_y = \
	old_dir_x * sin(speed) + play->ray.dir_y * cos(speed);
	play->ray.plane_x = \
	old_plane_x * cos(speed) - play->ray.plane_y * sin(speed);
	play->ray.plane_y = \
	old_plane_x * sin(speed) + play->ray.plane_y * cos(speed);
}

void	event_mouse(t_play *play)
{
	mlx_mouse_get_pos(play->win, \
	&play->player.mouse_x, &play->player.mouse_y);
	if (play->player.mouse_x < play->win_w && play->player.mouse_x > 0)
	{
		if (play->player.mouse_y < play->win_h && play->player.mouse_y > 0)
		{
			mlx_mouse_hide();
			play->key.mouse_mode = TRUE;
		}
		else
		{
			mlx_mouse_show();
			play->key.mouse_mode = FALSE;
		}
	}
	else
	{
		mlx_mouse_show();
		play->key.mouse_mode = FALSE;
	}
}
