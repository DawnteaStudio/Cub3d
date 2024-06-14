/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:42:21 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/14 19:58:15 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void fill_squares(t_map *map, int x, int y, int color)
{
	int i;
	int j;

	j = 0;
	while (j < (int)(MINIMAP * IMAGE_SIZE))
	{
		i = 0;
		while (i < (int)(MINIMAP * IMAGE_SIZE))
		{
			map->data[WINDOW_W * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

void	render_map(t_play *play, t_map *map)
{
	int col;
	int row;
	map->data = (int *)mlx_get_data_addr(map->img, &(map->bpp), &(map->line_size), &(map->endian));
	printf("%d\n", map->line_size);
	row = 0;
	while (row < map->y_size)
	{
		col = 0;
		while (col < (int)ft_strlen(map->field[row]))
		{
			if (map->field[row][col] == '1')
				fill_squares(map, (int)(MINIMAP * IMAGE_SIZE * col), (int)(MINIMAP * IMAGE_SIZE * row), GREEN);
			else if (map->field[row][col] == '0')
				fill_squares(map, (int)(MINIMAP * IMAGE_SIZE * col), (int)(MINIMAP * IMAGE_SIZE * row), WHITE);
			else
				fill_squares(map, (int)(MINIMAP * IMAGE_SIZE * col), (int)(MINIMAP * IMAGE_SIZE * row), SKYBLUE);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(play->mlx, play->win, map->img, 0, 0);
}

void	init_game(t_play *play)
{
	play->mlx = mlx_init();
	play->win = mlx_new_window(play->mlx, WINDOW_W, WINDOW_H, "cub3d");
	play->map.img = mlx_new_image(play->mlx, WINDOW_W, WINDOW_H);
	render_map(play, &play->map);
	mlx_loop(play->mlx);
}

// int	main(int argc, char **argv)
// {
// 	t_play	play;

// 	(void)argc;
// 	(void)argv;
	// if (argc != 2)
	// 	print_error(ERROR_STANDARD_INPUT);
	// initial_play(&play);
	// play.origin = read_map(argv[1]);
	// if (play.origin[0] == '\0')
	// 	print_error(ERROR_INVALID_FILE);
	// is_valid_info(&play);
	//game(&play);
// 	init_game(&play);
// 	return (0);
// }
