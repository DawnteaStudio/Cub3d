/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:31 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/23 10:57:36 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"

// mac key codes
# define LEFT_CLICK 1
# define ESC 53
# define KEY_PRESS 2
# define EXIT_BUTTON 17

# define TRUE 1
# define FALSE 0

# define MINIMAP 0.1
# define IMAGE_SIZE 80

# define MAP_ROW_SIZE 12
# define WINDOW_H (IMAGE_SIZE * MAP_ROW_SIZE)

# define MAP_COL_SIZE 20
# define WINDOW_W (IMAGE_SIZE * MAP_COL_SIZE)

// colors
# define WHITE 0xffffff
# define SKYBLUE 0x00ffff
# define GREEN 0x0A3711

typedef enum e_key_move
{
	KEY_A = 0,
	KEY_S,
	KEY_D,
	KEY_W = 13
}	t_key_move;

typedef enum e_key_direct
{
	KEY_LEFT = 123,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_UP
}	t_key_direct;

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

typedef struct s_image
{
	char	*path;
	void	*image;
	int		width;
	int		height;
}	t_image;

typedef struct s_map
{
	char	**field;
	int		start_y;
	int		start_x;
	int		direction;
	int		ceiling[3];
	int		floor[3];
	void	*image;
	int		*data;
	int		bpp;
	int		line_size;
	int		endian;
	int		y_size;
	int		x_size;
}	t_map;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	int		player_size;
	t_ray	player_ray;
	double	walk_speed;
	double	turn_speed;
	// double	rota_angle;
	// double	updown_sight;
}	t_player;

typedef struct s_play
{
	void		*mlx;
	void		*win;
	char		**origin;
	t_image		images[4];
	int			check_parsing;
	int			height;
	t_map		map;
	t_player	player;
}	t_play;

typedef struct s_node
{
	int				y;
	int				x;
	struct s_node	*next;
}	t_node;

typedef struct s_queue
{
	t_node	*front;
	t_node	*back;
}	t_queue;

typedef struct s_search
{
	int		*dy;
	int		*dx;
	int		idx;
	int		x;
	int		y;
	int		is_outside;
	t_queue	*queue;
}	t_search;

/* parse */
// read
char	**read_map(int *height, char *map_file);

// check_file
void	is_valid_file(char *file, int fd);

// check_info
void	is_valid_info(t_play *p);

// check_map
void	is_valid_map(int *idx, t_map *m);

// map_utils
void	make_field(t_play *p, int idx);

// bfs
void	find_component(t_map *m, int start_y, int start_x, int **visited);
void	find_space(t_map *m, int start_y, int start_x, int **visited);

// play
void	initial_play(t_play *play);
void	set_height(t_play *play);

// search
void	set_search(t_search *search);
void	free_search(t_search *search);

// extract_data
void	extract_path(t_play *p, int idx, int *width, int image_type);
void	extract_color(t_play *p, int *arr, int idx, int *width);

// print_error
void	print_error(int error_no);

// queue
void	q_pop(t_queue *q);
void	q_push(t_queue *q, t_node *node);
t_node	*make_node(int y, int x);
t_queue	*make_queue(void);

/* exec */

//init
void	init_game(t_play *play);
void	init_player(t_map *map, t_player *player);

//free
int		exit_game(t_play *play);

//keypress
int		key_press(int key, t_play *play);

//render
void	render_map(t_play *play, t_map *map);


//logic
int		main_loop(t_play *play);

#endif