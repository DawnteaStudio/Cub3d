/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:42:21 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/26 19:38:37 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	render_wall(t_play *play)
{
	int	i;
	int	j;
	int	height;

	i = 0;
	height = 0;
	while (i < play->win_h)
	{
		j = 0;
		while (j < play->win_w)
		{
			if (play->screen[i][j] != 0xfa0000)
				play->map.data[height] = play->screen[i][j];
			j++;
			height++;
		}
		i++;
	}
	mlx_put_image_to_window(play->mlx, play->win, play->map.image, 0, 0);
}

void	render_background(t_play *play)
{
	int	i;
	int	j;
	int	ceil;
	int	floor;

	ceil = play->map.ceiling[0] << 16 \
	| play->map.ceiling[1] << 8 | play->map.ceiling[2];
	floor = play->map.floor[0] << 16 \
	| play->map.floor[1] << 8 | play->map.floor[2];
	i = 0;
	while (i < play->win_h)
	{
		j = 0;
		while (j < play->win_w)
		{
			if (i < play->win_h / 2)
				play->screen[i][j] = ceil;
			else
				play->screen[i][j] = floor;
			j++;
		}
		i++;
	}
}

void	fill_squares(t_play *play, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < 8)
	{
		i = 0;
		while (i < 8)
		{
			play->mini.data[(21 * 8) * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

void	init_mini_map(t_play *play)
{
	play->mini.image = mlx_new_image(play->mlx, 8 * 21, 8 * 21);
	play->mini.data = (int *)mlx_get_data_addr(play->mini.image, \
	&(play->map.bpp), &(play->map.line_size), &(play->map.endian));
}

void	render_map(t_play *play)
{
	int	col;
	int	row;

	row = 0;
	while (row < play->mini.row_end - play->mini.row_start)
	{
		col = 0;
		while (col < play->mini.col_end - play->mini.col_start)
		{
			check_mini_maps(play, row, col);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(play->mlx, play->win, play->mini.image, 0, 0);
}
