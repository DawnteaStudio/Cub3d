/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:48:21 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/21 00:43:12 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int key, t_play *play)
{
	if (key == KEY_A)
		play->key.a = 1;
	if (key == KEY_S)
		play->key.s = 1;
	if (key == KEY_D)
		play->key.d = 1;
	if (key == KEY_W)
		play->key.w = 1;
	if (key == KEY_LEFT)
		play->key.left = 1;
	if (key == KEY_RIGHT)
		play->key.right = 1;
	if (key == ESC)
		exit_game(play);
	return (0);
}

int	key_release(int key, t_play *play)
{
	if (key == KEY_A)
		play->key.a = 0;
	if (key == KEY_S)
		play->key.s = 0;
	if (key == KEY_D)
		play->key.d = 0;
	if (key == KEY_W)
		play->key.w = 0;
	if (key == KEY_LEFT)
		play->key.left = 0;
	if (key == KEY_RIGHT)
		play->key.right = 0;
	return (0);
}
