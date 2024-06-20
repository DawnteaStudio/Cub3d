# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:06:13 by sewopark          #+#    #+#              #
#    Updated: 2024/06/20 22:30:50 by sewopark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d
INCLUDE	= include/
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
MLXFLAG	= -framework OpenGL -framework AppKit

PARSE	= check_file check_info extract_data main print_error play bfs \
			queue check_map read search
EXEC	= render free keypress init logic ray
SRCSNAME	= $(addprefix parse/, $(PARSE)) $(addprefix exec/, $(EXEC))
SRCS		= $(addsuffix .c, $(SRCSNAME))
OBJS		= $(addsuffix .o, $(SRCSNAME))
DEPS		= $(addsuffix .d, $(SRCSNAME))
LIBFT	= ./libft/libft.a
MLX_PATH	= minilibx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) $(MLX) -o $(NAME) $(MLXFLAG)

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