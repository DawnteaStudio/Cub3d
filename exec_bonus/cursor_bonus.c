/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:41:19 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/26 21:52:25 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	get_cursor_sprite(t_play *play, char *path)
{
	char	*real_path;

	real_path = ft_strjoin(path, ".xpm");
	if (play->cursor.image)
		mlx_destroy_image(play->mlx, play->cursor.image);
	play->cursor.image = mlx_xpm_file_to_image(play->mlx, \
	real_path, &play->door.width, &play->door.height);
	if (play->cursor.image == NULL)
		ft_error(MEMORY);
	free(real_path);
}

void	change_cursor1(t_play *play)
{
	static int	i = 10;
	char		*num;
	char		*path;

	num = ft_itoa(i / 10);
	path = ft_strjoin("./textures/v_", num);
	get_cursor_sprite(play, path);
	free(path);
	free(num);
	i++;
	if (i > 369)
		i = 10;
}
