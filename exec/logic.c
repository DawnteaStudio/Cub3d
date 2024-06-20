/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:08:35 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/20 22:18:57 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc(t_play *play)
{
	int	x;

	x = 0;
	while (x < play->win_w)
	{
		ray_setting(play, x);
		calc_size_dist_ray(play);
		calc_ray_hit(play);
		calc_draw_height(play);
		calc_hit_point_texture(play, x);
		x++;
	}
	render_wall(play);
}

int	main_loop(t_play *play)
{
	calc(play);
	return (0);
}