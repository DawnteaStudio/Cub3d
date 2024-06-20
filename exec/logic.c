/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:08:35 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/15 22:21:09 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	verLine(t_play *play, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(play->mlx, play->win, x, y, color);
		y++;
	}
}

void	calc(t_play *play)
{
	int	x;

	x = 0;
	int	width;

	width = WINDOW_W;
	while (x < width)
	{
		double cameraX = 2 * x / (double)width - 1;
		double rayDirX = play->player.player_ray.dir_x + play->player.player_ray.plane_x * cameraX;
		double rayDirY = play->player.player_ray.dir_y + play->player.player_ray.plane_y * cameraX;
		
		int mapX = (int)play->player.x;
		int mapY = (int)play->player.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (play->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - play->player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (play->player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - play->player.y) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (play->map.field[mapY][mapX] > 0) hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - play->player.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - play->player.y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(WINDOW_H / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + WINDOW_H / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WINDOW_H / 2;
		if(drawEnd >= WINDOW_H)
			drawEnd = WINDOW_H - 1;

		int	color;
		if (play->map.field[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (play->map.field[mapY][mapX] == 0)
			color = 0x00FF00;
		else
			color = 0xFFFF00;
		if (side == 1)
			color = color / 2;
		verLine(play, x, drawStart, drawEnd, color);
		x++;
	}
}

int	main_loop(t_play *play)
{
	calc(play);
	return (0);
}