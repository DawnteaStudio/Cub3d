/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:21:22 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/26 16:34:48 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	change_door(t_play *play, int y, int x)
{
	if (play->map.field[y][x] == 'D')
		play->map.field[y][x] = 'd';
	else if (play->map.field[y][x] == 'd')
		play->map.field[y][x] = 'D';
}

void	click_door(t_play *play)
{
	int	y;
	int	x;

	y = (int)play->player.y;
	x = (int)play->player.x;
	if (play->ray.dir_y < 0 && fabs(play->ray.dir_x) < 0.5)
		change_door(play, y - 1, x);
	else if (play->ray.dir_y > 0 && fabs(play->ray.dir_x) < 0.5)
		change_door(play, y + 1, x);
	else if (play->ray.dir_x < 0 && fabs(play->ray.dir_y) < 0.5)
		change_door(play, y, x - 1);
	else if (play->ray.dir_x > 0 && fabs(play->ray.dir_y) < 0.5)
		change_door(play, y, x + 1);
}
