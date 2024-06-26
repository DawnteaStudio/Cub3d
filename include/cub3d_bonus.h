/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:31 by sewopark          #+#    #+#             */
/*   Updated: 2024/06/26 22:30:34 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# define KEY_RELEASE 3
# define EXIT_BUTTON 17

# define TRUE 1
# define FALSE 0
# define CLOSE -1

# define MINIMAP 0.1
# define IMAGE_SIZE 64

# define MAP_ROW_SIZE 12
# define MAP_COL_SIZE 16

// colors
# define WHITE 0xffffff
# define SKYBLUE 0x00ffff
# define GREEN 0x0A3711
# define BLACK 0x000000
# define GRAY 0x738087
# define PLAYER 0xff0000

//wall
# define WALL_X 0
# define WALL_Y 1

//texture
# define TEXTURE 64

typedef enum e_key_move
{
	KEY_A = 0,
	KEY_S,
	KEY_D,
	KEY_Q = 12,
	KEY_W,
	KEY_SPACE = 49
}	t_key_move;

typedef enum e_key_direct
{
	KEY_LEFT = 123,
	KEY_RIGHT
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

typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	mouse_mode;
}	t_key;

typedef struct s_cursor
{
	void	*image;
	int		bpp;
	int		line_size;
	int		endian;
	int		width;
	int		height;
}	t_cursor;

typedef struct s_door
{
	int		*image;
	int		*close;
	int		*close_image;
	int		bpp;
	int		line_size;
	int		endian;
	int		width;
	int		height;
}	t_door;

typedef struct s_image
{
	char	*path;
	int		*image;
	int		bpp;
	int		line_size;
	int		endian;
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

typedef struct s_mini
{
	void	*image;
	int		*data;
	int		row_start;
	int		row_end;
	int		col_start;
	int		col_end;
	int		bpp;
	int		line_size;
	int		endian;
}	t_mini;

typedef struct s_wall
{
	int		draw_start;
	int		draw_end;
	int		line_h;
	int		texture_x;
	int		texture_y;
	double	wall_dist;
	double	wall_x;
	int		collision_wall;
	double	step;
	double	texture_p;
	int		index;
}	t_wall;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	ray_x;
	double	ray_y;
	double	plane_x;
	double	plane_y;
	double	delta_x;
	double	delta_y;
	double	size_x;
	double	size_y;
	int		is_door;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	int		step_x;
	int		step_y;
	int		mouse_x;
	int		mouse_y;
	int		player_size;
	double	walk_speed;
	double	turn_speed;
}	t_player;

typedef struct s_play
{
	void		*mlx;
	void		*win;
	int			win_h;
	int			win_w;
	int			**screen;
	char		**origin;
	t_image		images[4];
	int			check_parsing;
	int			height;
	t_map		map;
	t_mini		mini;
	t_player	player;
	t_ray		ray;
	t_wall		wall;
	t_key		key;
	t_door		door;
	t_cursor	cursor;
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

// bfs_utils
int		check_range(int y, int x, t_map *m);
int		find_next_idx(t_map *m, int y, int x, int **visited);
void	visit(t_queue *queue, int y, int x, int **visited);

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
void	init_player(t_play *play);

//free
int		exit_game(t_play *play);

//keypress
int		key_press(int key, t_play *play);
int		key_release(int key, t_play *play);

//render
void	render_map(t_play *play);
void	render_wall(t_play *play);
void	render_background(t_play *play);
void	fill_squares(t_play *play, int x, int y, int color);

//logic
int		main_loop(t_play *play);
void	check_texture_index(t_play *play);
void	init_mini_map(t_play *play);
void	check_mini_maps(t_play *play, int row, int col);

//ray
void	ray_setting(t_play *play, int x);
void	calc_size_dist_ray(t_play *play);
void	calc_ray_hit(t_play *play);
void	calc_draw_height(t_play *play);
void	calc_hit_point_texture(t_play *play, int x);

//key_move
void	move_w(t_play *play);
void	move_s(t_play *play);
void	move_a(t_play *play);
void	move_d(t_play *play);

//key_event
void	event_left(t_play *play);
void	event_right(t_play *play);
void	event_mouse(t_play *play);

//sprite
void	change_sprite(t_play *play);
void	render_sprite(t_play *play);
void	calc_sprite_ray(t_play *play);
void	get_sprite(t_play *play, char *path);

//door
void	click_door(t_play *play);

//cursor
void	change_cursor1(t_play *play);

#endif