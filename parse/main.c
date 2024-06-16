/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:07:53 by erho              #+#    #+#             */
/*   Updated: 2024/06/16 21:50:41 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_play	play;

	ft_memset(&play, 0, sizeof(play));
	if (argc != 2)
		print_error(ERROR_STANDARD_INPUT);
	initial_play(&play);
	play.origin = read_map(&(play.height), argv[1]);
	if (play.origin[0] == NULL)
		print_error(ERROR_INVALID_FILE);
	set_height(&play);
	is_valid_info(&play);
	// printf("============== test ==============\n");
	// for (int i=0; i<(int)play.map.y_size; i++)
	// 	printf("%s.\n", play.map.field[i]);
	// printf("============== test ==============\n");
	init_game(&play);
	return (0);
}
