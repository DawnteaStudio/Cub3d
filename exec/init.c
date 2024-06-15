/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:49:41 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/15 22:08:18 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player_direction(t_map *map, t_player *player)
{
	int	direction;

	direction = map->direction;
	if (direction == NORTH)
	{
		player->player_ray.dir_x = 0;
		player->player_ray.dir_y = 1;
	}
	else if (direction == SOUTH)
	{
		player->player_ray.dir_x = 0;
		player->player_ray.dir_y = -1;
	}
	else if (direction == WEST)
	{
		player->player_ray.dir_x = -1;
		player->player_ray.dir_y = 0;
	}
	else if (direction == EAST)
	{
		player->player_ray.dir_x = 1;
		player->player_ray.dir_y = 0;
	}
	player->player_ray.plane_x = 0;
	player->player_ray.plane_y = 0.66;
}

void	init_player(t_map *map, t_player *player)
{
	player->player_size = 10;
	player->x = map->start_x;
	player->y = map->start_y;
	player->walk_speed = 0.1;
	player->turn_speed = 0.1;
	init_player_direction(map, player);
}

void	init_game(t_play *play)
{
	play->mlx = mlx_init();
	play->win = mlx_new_window(play->mlx, WINDOW_W, WINDOW_H, "cub3d");
	play->map.image = mlx_new_image(play->mlx, WINDOW_W, WINDOW_H);
	render_map(play, &play->map);
	init_player(&play->map, &play->player);
	mlx_loop_hook(play->mlx, &main_loop, play);
	mlx_hook(play->win, EXIT_BUTTON, 0, &exit_game, play);
	mlx_hook(play->win, KEY_PRESS, 0, &key_press, play);
	mlx_loop(play->mlx);
}