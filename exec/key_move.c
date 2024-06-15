/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:45:48 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/21 01:05:26 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_w(t_play *play)
{
	double	speed;

	speed = play->player.walk_speed;
	if (play->map.field[(int)play->player.y] \
	[(int)(play->player.x + (play->ray.dir_x * speed))] == '0')
		play->player.x += play->ray.dir_x * speed;
	if (play->map.field[(int)(play->player.y + \
	(play->ray.dir_y * speed))][(int)play->player.x] == '0')
		play->player.y += play->ray.dir_y * speed;
}

void	move_s(t_play *play)
{
	double	speed;

	speed = play->player.walk_speed;
	speed = play->player.walk_speed;
	if (play->map.field[(int)play->player.y] \
	[(int)(play->player.x - (play->ray.dir_x * speed))] == '0')
		play->player.x -= play->ray.dir_x * speed;
	if (play->map.field[(int)(play->player.y - \
	(play->ray.dir_y * speed))][(int)play->player.x] == '0')
		play->player.y -= play->ray.dir_y * speed;
}

void	move_a(t_play *play)
{
	double	speed;

	speed = play->player.walk_speed;
	if (play->map.field[(int)play->player.y] \
	[(int)(play->player.x - (play->ray.plane_x * speed))] == '0')
		play->player.x -= play->ray.plane_x * speed;
	if (play->map.field[(int)(play->player.y - \
	(play->ray.plane_y * speed))][(int)play->player.x] == '0')
		play->player.y -= play->ray.plane_y * speed;
}

void	move_d(t_play *play)
{
	double	speed;

	speed = play->player.walk_speed;
	if (play->map.field[(int)play->player.y] \
	[(int)(play->player.x + (play->ray.plane_x * speed))] == '0')
		play->player.x += play->ray.plane_x * speed;
	if (play->map.field[(int)(play->player.y + \
	(play->ray.plane_y * speed))][(int)play->player.x] == '0')
		play->player.y += play->ray.plane_y * speed;
}
