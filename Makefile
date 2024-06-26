# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/23 10:58:30 by sewopark          #+#    #+#              #
#    Updated: 2024/06/26 15:55:30 by sewopark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d
INCLUDE	= include/
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
MLXFLAG	= -framework OpenGL -framework AppKit

PARSE	= check_file check_info extract_data main print_error play bfs \
			queue check_map read search map_utils
EXEC	= render free key init logic ray key_move key_event
BPARSE	= $(addsuffix _bonus, $(PARSE)) bfs_utils_bonus
BEXEC	= $(addsuffix _bonus, $(EXEC)) sprite_bonus door_bonus
SRCSNAME	= $(addprefix parse/, $(PARSE)) $(addprefix exec/, $(EXEC))
BSRCSNAME	= $(addprefix parse_bonus/, $(BPARSE)) \
			$(addprefix exec_bonus/, $(BEXEC))
SRCS		= $(addsuffix .c, $(SRCSNAME))
BSRCS		= $(addsuffix .c, $(BSRCSNAME))
OBJS		= $(addsuffix .o, $(SRCSNAME))
BOBJS		= $(addsuffix .o, $(BSRCSNAME))
DEPS		= $(addsuffix .d, $(SRCSNAME))
BDEPS		= $(addsuffix .d, $(BSRCSNAME))
LIBFT	= ./libft/libft.a
MLX_PATH	= minilibx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

ifdef WITH_BONUS
	OBJ_SWITCH = $(BOBJS)
	REMOVE = $(OBJS)
else
	OBJ_SWITCH = $(OBJS)
	REMOVE = $(BOBJS)
endif

all: $(NAME)
	$(info Building $(NAME)...)

$(NAME): $(OBJ_SWITCH) $(LIBFT) $(MLX)
	$(info Building OBJS...)
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJ_SWITCH) $(MLX) -o $(NAME) $(MLXFLAG)
	@$(RM) $(REMOVE)

-include $(DEPS) $(BDEPS)

%.o : %.c
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@ -MMD

$(LIBFT) :
	$(info Building LIBFT...)
	@make -C libft all
$(MLX) :	
	$(info Building MLX...)
	@make -C $(MLX_PATH)
bonus :
	$(info Starting cub3d bonus...)
	@make WITH_BONUS=1 all
clean:
	$(info Starting clean...)
	@make clean -C libft
	$(info Cleaning libft...)
	@make clean -C $(MLX_PATH)
	$(info Cleaning mlx...)
	@$(RM) $(OBJS)
	@$(RM) $(BOBJS)
	@$(RM) $(DEPS)
	@$(RM) $(BDEPS)

fclean: clean
	$(info Starting fclean...)
	$(info fcleaning libft...)
	@make fclean -C libft
	$(info fcleaning game...)
	@$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY : all clean fclean re bonus