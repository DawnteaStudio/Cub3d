/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:37:23 by erho              #+#    #+#             */
/*   Updated: 2024/06/04 16:18:22 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define MEMORY 50
# define LM 922337203685477580

# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t len);
int		ft_putstr(char *s);
int		ft_putchar(char c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_error(int error_no);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
int		ft_strcmp(char *s1, char *s2);
void	*ft_memset(void *ptr, int value, size_t num);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(char **));
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
int		ft_isalpha(int c);

#endif