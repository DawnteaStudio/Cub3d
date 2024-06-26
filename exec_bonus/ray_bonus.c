/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:49:17 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/26 16:14:08 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ray_setting(t_play *play, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)play->win_w - 1;
	play->ray.ray_x = play->ray.dir_x + play->ray.plane_x * camera_x;
	play->ray.ray_y = play->ray.dir_y + play->ray.plane_y * camera_x;
	play->map.start_x = (int)play->player.x;
	play->map.start_y = (int)play->player.y;
	if (play->ray.ray_x == 0)
		play->ray.delta_x = 1.1;
	else
		play->ray.delta_x = fabs(1 / play->ray.ray_x);
	if (play->ray.ray_y == 0)
		play->ray.delta_y = 1.1;
	else
		play->ray.delta_y = fabs(1 / play->ray.ray_y);
}

void	calc_size_dist_ray(t_play *play)
{
	t_ray	*tmp;

	tmp = &play->ray;
	if (tmp->ray_x < 0)
	{
		play->player.step_x = -1;
		tmp->size_x = (play->player.x - play->map.start_x) * tmp->delta_x;
	}
	else if (tmp->ray_x > 0)
	{
		play->player.step_x = 1;
		tmp->size_x = (play->map.start_x + 1.0 - play->player.x) * tmp->delta_x;
	}
	if (tmp->ray_y < 0)
	{
		play->player.step_y = -1;
		tmp->size_y = (play->player.y - play->map.start_y) * tmp->delta_y;
	}
	else if (tmp->ray_y > 0)
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
			play->wall.collision_wall = WALL_X;
		}
		else
		{
			play->ray.size_y += play->ray.delta_y;
			play->map.start_y += play->player.step_y;
			play->wall.collision_wall = WALL_Y;
		}
		if (play->map.field[play->map.start_y][play->map.start_x] == '1')
			break ;
	}
	if (play->wall.collision_wall == WALL_X)
		play->wall.wall_dist = (play->map.start_x - play->player.x + \
		(double)(1 - play->player.step_x) / 2) / play->ray.ray_x;
	else
		play->wall.wall_dist = (play->map.start_y - play->player.y + \
		(double)(1 - play->player.step_y) / 2) / play->ray.ray_y;
	play->wall.line_h = (int)(play->win_h / play->wall.wall_dist);
}

void	calc_draw_height(t_play *play)
{
	play->wall.draw_start = play->win_h / 2 - play->wall.line_h / 2;
	if (play->wall.draw_start < 0)
		play->wall.draw_start = 0;
	play->wall.draw_end = play->win_h / 2 + play->wall.line_h / 2;
	if (play->wall.draw_end >= play->win_h)
		play->wall.draw_end = play->win_h - 1;
	if (play->wall.collision_wall == WALL_X)
		play->wall.wall_x = play->player.y + play->wall.wall_dist \
		* play->ray.ray_y;
	else
		play->wall.wall_x = play->player.x + play->wall.wall_dist \
		* play->ray.ray_x;
	play->wall.wall_x -= floor(play->wall.wall_x);
	play->wall.texture_x = (int)(play->wall.wall_x * TEXTURE);
	if (play->wall.collision_wall == WALL_X && play->ray.ray_x < 0)
		play->wall.texture_x = TEXTURE - play->wall.texture_x - 1;
	if (play->wall.collision_wall == WALL_Y && play->ray.ray_y > 0)
		play->wall.texture_x = TEXTURE - play->wall.texture_x - 1;
	play->wall.step = (double)TEXTURE / (double)play->wall.line_h;
}

void	calc_hit_point_texture(t_play *play, int x)
{
	int	i;

	check_texture_index(play);
	i = play->wall.draw_start;
	play->wall.texture_p = (i - (int)play->win_h / 2 \
	+ (int)play->wall.line_h / 2) * play->wall.step;
	while (i < play->wall.draw_end)
	{
		play->wall.texture_y = (int)play->wall.texture_p & (TEXTURE - 1);
		play->wall.texture_p += play->wall.step;
		if (play->ray.is_door == FALSE)
			play->screen[i][x] = play->images[play->wall.index].image[TEXTURE * \
			play->wall.texture_y + play->wall.texture_x];
		else if (play->ray.is_door == TRUE)
			play->screen[i][x] = play->door.image[TEXTURE * \
			play->wall.texture_y + play->wall.texture_x];
		else if (play->ray.is_door == CLOSE)
			play->screen[i][x] = play->door.close[TEXTURE * \
			play->wall.texture_y + play->wall.texture_x];
		i++;
	}
}
