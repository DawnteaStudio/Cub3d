/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:08:35 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/23 18:41:25 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	check_keys(t_play *play)
{
	event_mouse(play);
	if (play->key.w)
		move_w(play);
	if (play->key.a)
		move_a(play);
	if (play->key.s)
		move_s(play);
	if (play->key.d)
		move_d(play);
	if (play->key.left || (play->player.mouse_x < play->win_w / 2 - (play->win_w * 0.3) && play->key.mouse_mode == TRUE))
		event_left(play);
	if (play->key.right || (play->player.mouse_x > play->win_w / 2 + (play->win_w * 0.3) && play->key.mouse_mode == TRUE))
		event_right(play);
}

void	check_texture_index(t_play *play)
{
	if (play->wall.collision_wall == WALL_X)
	{
		if (play->ray.ray_x < 0)
			play->wall.index = EAST;
		else
			play->wall.index = WEST;
	}
	else
	{
		if (play->ray.ray_y < 0)
			play->wall.index = SOUTH;
		else
			play->wall.index = NORTH;
	}
}

void	calc(t_play *play)
{
	int	x;

	x = 0;
	mlx_clear_window(play->mlx, play->win);
	render_background(play);
	while (x < play->win_w)
	{
		ray_setting(play, x);
		calc_size_dist_ray(play);
		calc_ray_hit(play);
		calc_draw_height(play);
		calc_hit_point_texture(play, x);
		x++;
	}
	check_keys(play);
	render_wall(play);
}

int	main_loop(t_play *play)
{
	calc(play);
	// render_map(play);
	return (0);
}
