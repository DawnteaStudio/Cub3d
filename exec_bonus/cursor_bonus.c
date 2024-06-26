/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:41:19 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/26 21:06:07 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	get_cursor_sprite(t_play *play, char *path)
{
	if (play->cursor.image)
		mlx_destroy_image(play->mlx, play->cursor.image);
	play->cursor.image = mlx_xpm_file_to_image(play->mlx, \
	path, &play->door.width, &play->door.height);
}

void	change_cursor4(t_play *play, int *i)
{
	if (*i % 280 == 0)
		get_cursor_sprite(play, "./textures/v_28.xpm");
	if (*i % 290 == 0)
		get_cursor_sprite(play, "./textures/v_29.xpm");
	if (*i % 300 == 0)
		get_cursor_sprite(play, "./textures/v_30.xpm");
	if (*i % 310 == 0)
		get_cursor_sprite(play, "./textures/v_31.xpm");
	if (*i % 320 == 0)
		get_cursor_sprite(play, "./textures/v_32.xpm");
	if (*i % 330 == 0)
		get_cursor_sprite(play, "./textures/v_33.xpm");
	if (*i % 340 == 0)
		get_cursor_sprite(play, "./textures/v_34.xpm");
	if (*i % 350 == 0)
		get_cursor_sprite(play, "./textures/v_35.xpm");
	if (*i % 360 == 0)
	{
		get_cursor_sprite(play, "./textures/v_36.xpm");
		return ;
	}
	(*i)++;
}

void	change_cursor3(t_play *play, int *i)
{
	if (*i % 190 == 0)
		get_cursor_sprite(play, "./textures/v_19.xpm");
	if (*i % 200 == 0)
		get_cursor_sprite(play, "./textures/v_20.xpm");
	if (*i % 210 == 0)
		get_cursor_sprite(play, "./textures/v_21.xpm");
	if (*i % 220 == 0)
		get_cursor_sprite(play, "./textures/v_22.xpm");
	if (*i % 230 == 0)
		get_cursor_sprite(play, "./textures/v_23.xpm");
	if (*i % 240 == 0)
		get_cursor_sprite(play, "./textures/v_24.xpm");
	if (*i % 250 == 0)
		get_cursor_sprite(play, "./textures/v_25.xpm");
	if (*i % 260 == 0)
		get_cursor_sprite(play, "./textures/v_26.xpm");
	if (*i % 270 == 0)
	{
		get_cursor_sprite(play, "./textures/v_27.xpm");
		change_cursor4(play, i);
		return ;
	}
	(*i)++;
}

void	change_cursor2(t_play *play, int *i)
{
	if (*i % 100 == 0)
		get_cursor_sprite(play, "./textures/v_10.xpm");
	if (*i % 110 == 0)
		get_cursor_sprite(play, "./textures/v_11.xpm");
	if (*i % 120 == 0)
		get_cursor_sprite(play, "./textures/v_12.xpm");
	if (*i % 130 == 0)
		get_cursor_sprite(play, "./textures/v_13.xpm");
	if (*i % 140 == 0)
		get_cursor_sprite(play, "./textures/v_14.xpm");
	if (*i % 150 == 0)
		get_cursor_sprite(play, "./textures/v_15.xpm");
	if (*i % 160 == 0)
		get_cursor_sprite(play, "./textures/v_16.xpm");
	if (*i % 170 == 0)
		get_cursor_sprite(play, "./textures/v_17.xpm");
	if (*i % 180 == 0)
	{
		get_cursor_sprite(play, "./textures/v_18.xpm");
		change_cursor3(play, i);
		return ;
	}
	(*i)++;
}

void	change_cursor1(t_play *play)
{
	static int	i = 0;

	if (i % 10 == 0)
		get_cursor_sprite(play, "./textures/v_1.xpm");
	if (i % 20 == 0)
		get_cursor_sprite(play, "./textures/v_2.xpm");
	if (i % 30 == 0)
		get_cursor_sprite(play, "./textures/v_3.xpm");
	if (i % 40 == 0)
		get_cursor_sprite(play, "./textures/v_4.xpm");
	if (i % 50 == 0)
		get_cursor_sprite(play, "./textures/v_5.xpm");
	if (i % 60 == 0)
		get_cursor_sprite(play, "./textures/v_6.xpm");
	if (i % 70 == 0)
		get_cursor_sprite(play, "./textures/v_7.xpm");
	if (i % 80 == 0)
		get_cursor_sprite(play, "./textures/v_8.xpm");
	if (i % 90 == 0)
	{
		get_cursor_sprite(play, "./textures/v_9.xpm");
		change_cursor2(play, &i);
		i = 0;
	}
	i++;
}
