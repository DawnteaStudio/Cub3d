/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:51:13 by parksewon         #+#    #+#             */
/*   Updated: 2024/06/26 22:02:51 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	check_sprite(t_play *play)
{
	if (play->map.field[play->map.start_y][play->map.start_x] == '1')
	{
		play->ray.is_door = FALSE;
		return (TRUE);
	}
	else if (play->map.field[play->map.start_y][play->map.start_x] == 'D')
	{
		play->ray.is_door = TRUE;
		return (TRUE);
	}
	else if (play->map.field[play->map.start_y][play->map.start_x] == 'd')
	{
		play->ray.is_door = CLOSE;
		return (TRUE);
	}
	return (FALSE);
}

void	calc_sprite_ray(t_play *play)
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
		if (check_sprite(play) == TRUE)
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

void	render_sprite(t_play *play)
{
	int	x;

	x = 0;
	while (x < play->win_w)
	{
		ray_setting(play, x);
		calc_size_dist_ray(play);
		calc_sprite_ray(play);
		calc_draw_height(play);
		calc_hit_point_texture(play, x);
		x++;
	}
	render_wall(play);
}

void	get_sprite(t_play *play, char *path)
{
	void	*tmp_img;

	tmp_img = (int *)mlx_xpm_file_to_image(play->mlx, path, \
	&play->door.width, &play->door.height);
	if (tmp_img == NULL)
		ft_error(MEMORY);
	play->door.image = (int *)mlx_get_data_addr(tmp_img, &(play->door.bpp), \
	&(play->door.line_size), &(play->door.endian));
	if (play->door.image == NULL)
		ft_error(MEMORY);
}

void	change_sprite(t_play *play)
{
	static int	i = 0;

	if (i % 10 == 0)
		get_sprite(play, "./textures/portal1.xpm");
	if (i % 20 == 0)
		get_sprite(play, "./textures/portal2.xpm");
	if (i % 30 == 0)
		get_sprite(play, "./textures/portal3.xpm");
	if (i % 40 == 0)
		get_sprite(play, "./textures/portal4.xpm");
	if (i % 50 == 0)
		get_sprite(play, "./textures/portal5.xpm");
	if (i % 60 == 0)
		get_sprite(play, "./textures/portal6.xpm");
	if (i % 70 == 0)
		get_sprite(play, "./textures/portal7.xpm");
	if (i % 80 == 0)
		get_sprite(play, "./textures/portal8.xpm");
	if (i % 90 == 0)
	{
		get_sprite(play, "./textures/portal9.xpm");
		i = 0;
	}
	i++;
}
