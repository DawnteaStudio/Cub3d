/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:49:41 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/21 09:13:49 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_texture(t_play *play, void *tmp, int i)
{
	int	pixel;
	int	*tmp_addr;

	pixel = 0;
	play->images[i].image = \
	(int *)malloc(sizeof(int) * play->win_h * play->win_w);
	if (play->images->image == NULL)
		ft_error(MEMORY);
	tmp_addr = (int *)mlx_get_data_addr(tmp, \
	&(play->images[i].bpp), &(play->images[i].line_size), \
	&(play->images[i].endian));
	while (pixel < play->win_h * play->win_w)
	{
			play->images[i].image[pixel] = tmp_addr[pixel];
			pixel++;
	}
	mlx_destroy_image(play->mlx, tmp);
}

void	init_screen(t_play *play)
{
	int		i;
	void	*tmp_img;

	i = 0;
	while (i < 4)
	{
		tmp_img = mlx_xpm_file_to_image
			(play->mlx, play->images[i].path, &play->images[i].width, \
			&play->images[i].height);
		if (tmp_img == NULL)
			ft_error(MEMORY);
		init_texture(play, tmp_img, i);
		i++;
	}
	i = 0;
	play->screen = (int **)malloc(sizeof(int *) * play->win_h);
	if (play->screen == NULL)
		ft_error(MEMORY);
	while (i < play->win_h)
	{
		play->screen[i] = (int *)malloc(sizeof(int) * play->win_w);
		if (play->screen[i] == NULL)
			ft_error(MEMORY);
		i++;
	}
}


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
		play->ray.plane_x = -0.66;
	}
	else if (direction == WEST)
	{
		play->ray.dir_x = -1;
		play->ray.plane_y = -0.66;
	}
	else if (direction == EAST)
	{
		play->ray.dir_x = 1;
		play->ray.plane_y = 0.66;
	}
}

void	init_player(t_play *play)
{
	play->player.player_size = 10;
	play->player.x = (play->map.start_x) + 0.5;
	play->player.y = (play->map.start_y) + 0.5;
	play->player.walk_speed = 0.1;
	play->player.turn_speed = 0.05;
	init_player_direction(play);
	play->map.field[play->map.start_y][play->map.start_x] = '0';
}

void	init_game(t_play *play)
{
	play->win_h = IMAGE_SIZE * MAP_ROW_SIZE;
	play->win_w = IMAGE_SIZE * MAP_COL_SIZE;
	play->mlx = mlx_init();
	play->win = mlx_new_window(play->mlx, play->win_w, play->win_h, "cub3d");
	play->map.image = mlx_new_image(play->mlx, play->win_w, play->win_h);
	play->map.data = (int *)mlx_get_data_addr(play->map.image, \
	&(play->map.bpp), &(play->map.line_size), &(play->map.endian));
	init_screen(play);
	init_player(play);
	mlx_loop_hook(play->mlx, &main_loop, play);
	mlx_hook(play->win, EXIT_BUTTON, 0, &exit_game, play);
	mlx_hook(play->win, KEY_PRESS, 0, &key_press, play);
	mlx_hook(play->win, KEY_RELEASE, 0, &key_release, play);
	mlx_loop(play->mlx);
}
