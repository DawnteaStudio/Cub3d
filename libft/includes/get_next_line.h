/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:14:16 by erho              #+#    #+#             */
/*   Updated: 2024/05/08 19:30:41 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_fopen
{
	int		read_size;
	char	*buff;
	size_t	str_size;
	int		is_newline;
}	t_fopen;

char	*get_next_line(int fd);
size_t	gnl_strlcat(char *dest, char *src, size_t len);
char	*gnl_strndup(char *str, int len);
char	*gnl_strjoin(char **s1, t_fopen fopen);
char	*move_address(char **lst, size_t str_size);
int		find_newline(char *lst, t_fopen *fopen);
char	*insert_newline(char **lst);
void	read_line(int fd, char	**lst);

#endif
