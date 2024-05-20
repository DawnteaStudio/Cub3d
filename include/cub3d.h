/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:31 by sewopark          #+#    #+#             */
/*   Updated: 2024/05/20 16:53:13 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define IMAGE_SIZE 64

// mask code
# define KEY_PRESS_MASK 1

// mac key codes
# define LEFT_CLICK 1
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define ESC 53
# define KEY_PRESS 2
# define EXIT_BUTTON 17

# define TRUE 1
# define FALSE 0

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_direction;

typedef enum e_error_type
{
	VALID,
	ERROR_OTHER_CHARACTERS,
	ERROR_FILE_NAME,
	ERROR_STANDARD_INPUT,
	ERROR_INVALID_FILE,
	ERROR_INVALID_MAP,
	ERROR_INVALID_INFO,
	ERROR_MAP_SIZE
}	t_error_type;

# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

typedef struct s_image {
	char	*path;
	void	*image;
	int		width;
	int		height;
}	t_image;

typedef struct s_map
{
	char	**split_map;
	int		start_y;
	int		start_x;
	int		direction;
	int		ceiling[3];
	int		floor[3];
	size_t	y_size;
	size_t	x_size;
}	t_map;

typedef struct s_play {
	void	*mlx;
	void	*win;
	char	*origin;
	size_t	origin_len;
	t_image	images[4];
	int		check_parsing;
	int		y;
	int		x;
	t_map	map;
}	t_play;

/* parse */
// length
size_t	ft_exp_len(char **str);

// check_file
void	is_valid_file(char *file, int fd);

// check_info
void	is_valid_info(t_play *p);

// set_play
void	initial_play(t_play *play);

// split_map
char	**split_map(char const *s, char c);

// extract_data
void	extract_path(t_play *p, size_t *idx, int image_type);
void	extract_color(t_play *p, int *arr, size_t *idx);

// print_error
void	print_error(int error_no);

#endif