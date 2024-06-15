/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:26:25 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/15 19:39:49 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	exit_game(t_play *play)
{
	if (play && play->map.image)
		mlx_destroy_image(play->mlx, play->map.image);
	if (play->win)
		mlx_destroy_window(play->mlx, play->win);
	exit(0);
	return (0);
}