/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:08:35 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/26 21:02:24 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	check_mini_maps(t_play *play, int row, int col)
{
	int	s_start;
	int	c_start;

	s_start = play->mini.row_start;
	c_start = play->mini.col_start;
	fill_squares(play, 8 * col, 8 * row, BLACK);
	if (s_start + row >= play->map.y_size || c_start + col >= play->map.x_size)
		return ;
	else if (s_start + row < 0 || c_start + col < 0)
		return ;
	else if (s_start + row == (int)play->player.y \
	&& c_start + col == (int)play->player.x)
		fill_squares(play, 8 * col, 8 * row, PLAYER);
	else if (play->map.field[s_start + row][c_start + col] == '1')
		fill_squares(play, 8 * col, 8 * row, GREEN);
	else if (play->map.field[s_start + row][c_start + col] == '0')
		fill_squares(play, 8 * col, 8 * row, WHITE);
	else if (play->map.field[s_start + row][c_start + col] == 'D')
		fill_squares(play, 8 * col, 8 * row, SKYBLUE);
	else if (play->map.field[s_start + row][c_start + col] == 'd')
		fill_squares(play, 8 * col, 8 * row, GRAY);
	else if (play->map.field[s_start + row][c_start + col] == 0)
		fill_squares(play, 8 * col, 8 * row, BLACK);
}

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
	if (play->key.left || (play->player.mouse_x < \
	play->win_w / 2 - (play->win_w * 0.3) && play->key.mouse_mode == TRUE))
		event_left(play);
	if (play->key.right || (play->player.mouse_x > \
	play->win_w / 2 + (play->win_w * 0.3) && play->key.mouse_mode == TRUE))
		event_right(play);
	if (play->key.mouse_mode == TRUE)
	{
		mlx_put_image_to_window(play->mlx, play->win, play->cursor.image, \
		play->player.mouse_x - 4, play->player.mouse_y - 4);
	}
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
	change_sprite(play);
	change_cursor1(play);
	play->ray.is_door = FALSE;
	while (x < play->win_w)
	{
		ray_setting(play, x);
		calc_size_dist_ray(play);
		calc_ray_hit(play);
		calc_draw_height(play);
		calc_hit_point_texture(play, x);
		x++;
	}
	render_wall(play);
	render_sprite(play);
	check_keys(play);
}

int	main_loop(t_play *play)
{
	calc(play);
	play->mini.col_start = (int)play->player.x - 10;
	play->mini.col_end = (int)play->player.x + 10;
	play->mini.row_start = (int)play->player.y - 10;
	play->mini.row_end = (int)play->player.y + 10;
	render_map(play);
	return (0);
}
