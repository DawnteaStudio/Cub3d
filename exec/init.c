/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:49:41 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/16 22:08:38 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player_direction(t_play *play)
{
	int	direction;

	direction = play->map.direction;
	if (direction == NORTH)
	{
		play->ray.dir_y = -1;
		play->ray.plane_x = 0.66;
	}
	else if (direction == SOUTH)
	{
		play->ray.dir_y = 1;
		play->ray.plane_x = 0.66;
	}
	else if (direction == WEST)
	{
		play->ray.dir_x = -1;
		play->ray.plane_y = -0.66;
	}
	else if (direction == EAST)
	{
		play->ray.dir_x = 1;
		play->ray.plane_y = -0.66;
	}
}

void	init_player(t_play *play)
{
	play->player.player_size = 10;
	play->player.x = play->map.start_x;
	play->player.y = play->map.start_y;
	play->player.walk_speed = 1.0;
	play->player.turn_speed = 0.1;
	init_player_direction(play);
}

void	init_game(t_play *play)
{
	play->win_h = IMAGE_SIZE * MAP_ROW_SIZE;
	play->win_w = IMAGE_SIZE * MAP_COL_SIZE;
	play->mlx = mlx_init();
	play->win = mlx_new_window(play->mlx, play->win_h, play->win_w, "cub3d");
	play->map.image = mlx_new_image(play->mlx, play->win_h, play->win_w);
	render_map(play);
	init_player(play);
	// mlx_loop_hook(play->mlx, &main_loop, play);
	mlx_hook(play->win, EXIT_BUTTON, 0, &exit_game, play);
	mlx_hook(play->win, KEY_PRESS, 0, &key_press, play);
	mlx_loop(play->mlx);
}