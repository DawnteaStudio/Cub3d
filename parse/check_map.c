/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:16:04 by erho              #+#    #+#             */
/*   Updated: 2024/05/09 05:01:42 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	is_valid_map_config(t_map *m, int y, int x)
// {
// 	if ((y == 0 || y == (int)m->y_size - 1) && m->split_map[y][x] != '1')
// 		print_error(INVALID_MAP);
// 	if ((x == 0 || x == (int)m->x_size - 1) && m->split_map[y][x] != '1')
// 		print_error(INVALID_MAP);
// 	if (m->split_map[y][x] != '0' && m->split_map[y][x] != '1'
// 			&& m->split_map[y][x] != 'C' && m->split_map[y][x] != 'E'
// 			&& m->split_map[y][x] != 'P')
// 		print_error(INVALID_MAP);
// 	if (m->split_map[y][x] == 'P')
// 	{
// 		m->start_y = y;
// 		m->start_x = x;
// 		m->start_cnt++;
// 	}
// 	else if (m->split_map[y][x] == 'C')
// 		m->collection_cnt++;
// 	else if (m->split_map[y][x] == 'E')
// 		m->end_cnt++;
// }


