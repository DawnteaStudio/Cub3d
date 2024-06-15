# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erho <erho@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:06:13 by sewopark          #+#    #+#              #
#    Updated: 2024/06/16 00:01:58 by erho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d
INCLUDE	= include/
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

PARSE	= check_file check_info extract_data main print_error play bfs \
			queue check_map read search map_utils
SRCSNAME	= $(addprefix parse/, $(PARSE))
SRCS		= $(addsuffix .c, $(SRCSNAME))
OBJS		= $(addsuffix .o, $(SRCSNAME))
DEPS		= $(addsuffix .d, $(SRCSNAME))
LIBFT	= ./libft/libft.a
MLX_PATH	= minilibx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS)  -o $(NAME)

-include $(DEPS)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@ -MMD

$(LIBFT) :
	make -C libft all
$(MLX) :
	make -C $(MLX_PATH)

clean:
	make clean -C libft
	make clean -C $(MLX_PATH)
	$(RM) $(OBJS)
	$(RM) $(DEPS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY : all clean fclean re