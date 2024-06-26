/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksewon <parksewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:51:13 by parksewon         #+#    #+#             */
/*   Updated: 2024/06/25 21:17:37 by parksewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	init_sprite(t_play *play)
{
	play->door.wall_dist = 0;
	play->door.line_h = 0;
	play->door.draw_start = 0;
	play->door.draw_end = 0;
}

void	get_sprite(t_play *play, char *path)
{
	void	*tmp_img;

	if (play->door.image != NULL)
		free(play->door.image);
	play->door.image = (int *)malloc(sizeof(int) * TEXTURE * TEXTURE);
	tmp_img = (int *)mlx_xpm_file_to_image(play->mlx, path, \
	&play->door.width, &play->door.height);
	if (play->door.image == NULL || tmp_img == NULL)
		ft_error(MEMORY);
	play->door.image = (int *)mlx_get_data_addr(tmp_img, &(play->door.bpp), \
	&(play->door.line_size), &(play->door.endian));
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
