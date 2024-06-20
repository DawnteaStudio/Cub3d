/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:48:21 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/15 22:04:29 by sewopark         ###   ########.fr       */
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
	if (key == ESC)
		exit_game(play);
	return (0);
}


	// //rotate to the right
	// if (key == KEY_D)
	// {
	// 	//both camera direction and camera plane must be rotated
	// 	double oldplayer_ray.dir_x = player->player_ray.dir_x;
	// 	player->player_ray.dir_x = player->player_ray.dir_x * cos(-player->turn_speed) - player->player_ray.dir_y * sin(-player->turn_speed);
	// 	player->player_ray.dir_y = oldplayer_ray.dir_x * sin(-player->turn_speed) + player->player_ray.dir_y * cos(-player->turn_speed);
	// 	double oldPlaneX = player->planeX;
	// 	player->planeX = player->planeX * cos(-player->turn_speed) - player->planeY * sin(-player->turn_speed);
	// 	player->planeY = oldPlaneX * sin(-player->turn_speed) + player->planeY * cos(-player->turn_speed);
	// }
	// //rotate to the left
	// if (key == KEY_A)
	// {
	// 	//both camera direction and camera plane must be rotated
	// 	double oldplayer_ray.dir_x = player->player_ray.dir_x;
	// 	player->player_ray.dir_x = player->player_ray.dir_x * cos(player->turn_speed) - player->player_ray.dir_y * sin(player->turn_speed);
	// 	player->player_ray.dir_y = oldplayer_ray.dir_x * sin(player->turn_speed) + player->player_ray.dir_y * cos(player->turn_speed);
	// 	double oldPlaneX = player->planeX;
	// 	player->planeX = player->planeX * cos(player->turn_speed) - player->planeY * sin(player->turn_speed);
	// 	player->planeY = oldPlaneX * sin(player->turn_speed) + player->planeY * cos(player->turn_speed);
	// }