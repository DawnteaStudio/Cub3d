# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:06:13 by sewopark          #+#    #+#              #
#    Updated: 2024/05/03 16:33:36 by sewopark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d
INCLUDE	= include/
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

SRCS	= main.c
OBJS	= $(SRCS:%.c=%.o)
LIBFT	= ./libft/libft.a
MLX_PATH	= minilibx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS)  -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(LIBFT) :
	make -C libft all
$(MLX) :
	make -C $(MLX_PATH)

clean:
	make clean -C libft
	make clean -C $(MLX_PATH)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY : all clean fclean re