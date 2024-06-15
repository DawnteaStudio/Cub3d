/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:48:21 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/15 22:30:44 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int key, t_play *play)
{
	if (key == KEY_W)
	{
		if (!play->map.field[(int)(play->player.y)][(int)(play->player.x + play->player.player_ray.dir_x * play->player.walk_speed)])
			play->player.x += play->player.player_ray.dir_x * play->player.walk_speed;
		if (!play->map.field[(int)(play->player.y+ play->player.player_ray.dir_y * play->player.walk_speed)][(int)(play->player.x)])
			play->player.y += play->player.player_ray.dir_y * play->player.walk_speed;
		printf("%c\n", play->map.field[(int)(play->player.y)][(int)(play->player.x + play->player.player_ray.dir_x * play->player.walk_speed)]);
	}
	if (key == KEY_S)
	{
		if (!play->map.field[(int)(play->player.y)][(int)(play->player.x - play->player.player_ray.dir_x * play->player.walk_speed)])
			play->player.x -= play->player.player_ray.dir_x * play->player.walk_speed;
		if (!play->map.field[(int)(play->player.y - play->player.player_ray.dir_y * play->player.walk_speed)][(int)(play->player.x)])
			play->player.y -= play->player.player_ray.dir_y * play->player.walk_speed;
		printf("%c\n", play->map.field[(int)(play->player.y)][(int)(play->player.x - play->player.player_ray.dir_x * play->player.walk_speed)]);
	}
	//rotate to the right
	if (key == KEY_RIGHT)
	{
		//both camera direction and camera plane must be rotated
		double old_dirX = play->player.player_ray.dir_x;
		play->player.player_ray.dir_x = play->player.player_ray.dir_x * cos(-play->player.turn_speed) - play->player.player_ray.dir_y * sin(-play->player.turn_speed);
		play->player.player_ray.dir_y = old_dirX * sin(-play->player.turn_speed) + play->player.player_ray.dir_y * cos(-play->player.turn_speed);
		double oldPlaneX = play->player.player_ray.plane_x;
		play->player.player_ray.plane_x = play->player.player_ray.plane_x * cos(-play->player.turn_speed) - play->player.player_ray.plane_y * sin(-play->player.turn_speed);
		play->player.player_ray.plane_y = oldPlaneX * sin(-play->player.turn_speed) + play->player.player_ray.plane_y * cos(-play->player.turn_speed);
	}
	//rotate to the left
	if (key == KEY_LEFT)
	{
		//both camera direction and camera plane must be rotated
		double old_dirX = play->player.player_ray.dir_x;
		play->player.player_ray.dir_x = play->player.player_ray.dir_x * cos(play->player.turn_speed) - play->player.player_ray.dir_y * sin(play->player.turn_speed);
		play->player.player_ray.dir_y = old_dirX * sin(play->player.turn_speed) + play->player.player_ray.dir_y * cos(play->player.turn_speed);
		double oldPlaneX = play->player.player_ray.plane_x;
		play->player.player_ray.plane_x = play->player.player_ray.plane_x * cos(play->player.turn_speed) - play->player.player_ray.plane_y * sin(play->player.turn_speed);
		play->player.player_ray.plane_y = oldPlaneX * sin(play->player.turn_speed) + play->player.player_ray.plane_y * cos(play->player.turn_speed);
	}
	if (key == ESC)
		exit_game(play);
	return (0);
}


