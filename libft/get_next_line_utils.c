/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:14:36 by erho              #+#    #+#             */
/*   Updated: 2024/05/08 20:24:12 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*gnl_strndup(char *str, int len)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		ft_error(MEMORY);
	i = 0;
	while (str[i] && i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

size_t	gnl_strlcat(char *dest, char *src, size_t len)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	dest_len = 0;
	src_len = 0;
	while (dest && dest[dest_len])
		dest_len++;
	dest += dest_len;
	while (src[src_len])
		src_len++;
	if (len <= dest_len)
		return (len + src_len);
	while (src[i] && dest_len + i + 1 < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}

char	*gnl_strjoin(char **s1, t_fopen fopen)
{
	char	*res;
	size_t	len;
	size_t	s1_len;

	len = 0;
	while ((*s1)[len])
		len++;
	s1_len = len;
	len += (size_t)fopen.read_size;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		ft_error(MEMORY);
	res[0] = '\0';
	gnl_strlcat(res, *s1, s1_len + 1);
	gnl_strlcat(res, fopen.buff, len + 1);
	free(*s1);
	return (res);
}
