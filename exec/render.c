/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:42:21 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/21 01:29:27 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

	i = 0;
	while (i < play->win_h)
	{
		j = 0;
		while (j < play->win_w)
		{
			if (i < play->win_h / 2)
				play->screen[i][j] = SKYBLUE;
			else
				play->screen[i][j] = GREEN;
			j++;
		}
		i++;
	}
}

void	fill_squares(t_play *play, int x, int y, int color)
{
	int i;
	int j;

	j = 0;
	while (j < (int)(MINIMAP * IMAGE_SIZE))
	{
		i = 0;
		while (i < (int)(MINIMAP * IMAGE_SIZE))
		{
			play->map.data[play->win_w * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

void	render_map(t_play *play)
{
	int col;
	int row;
	play->map.data = (int *)mlx_get_data_addr(play->map.image, &(play->map.bpp), &(play->map.line_size), &(play->map.endian));
	row = 0;
	while (row < play->map.y_size)
	{
		col = 0;
		while (col < (int)ft_strlen(play->map.field[row]))
		{
			if (play->map.field[row][col] == '1')
				fill_squares(play, (int)(MINIMAP * IMAGE_SIZE * col), (int)(MINIMAP * IMAGE_SIZE * row), GREEN);
			else if (play->map.field[row][col] == '0')
				fill_squares(play, (int)(MINIMAP * IMAGE_SIZE * col), (int)(MINIMAP * IMAGE_SIZE * row), WHITE);
			else
				fill_squares(play, (int)(MINIMAP * IMAGE_SIZE * col), (int)(MINIMAP * IMAGE_SIZE * row), SKYBLUE);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(play->mlx, play->win, play->map.image, 0, 0);
}
