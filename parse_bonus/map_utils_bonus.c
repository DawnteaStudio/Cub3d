/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:24:55 by erho              #+#    #+#             */
/*   Updated: 2024/06/23 14:59:46 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

char	*replace_field(char *str, int x_size, int str_len)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (x_size + 1));
	if (res == NULL)
		ft_error(MEMORY);
	res[x_size] = '\0';
	ft_strlcpy(res, str, str_len + 1);
	ft_memset(res + str_len, ' ', sizeof(char) * (x_size - str_len));
	free(str);
	return (res);
}

int	find_x_size(int y_size, char **tmp)
{
	int	tmp_x_size;
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (i < y_size)
	{
		tmp_x_size = (int)ft_strlen(tmp[i]);
		if (tmp_x_size > res)
			res = tmp_x_size;
		i++;
	}
	return (res);
}

void	make_field(t_play *p, int idx)
{
	char	**tmp;
	int		i;
	int		tmp_x_size;

	tmp = &(p->origin[idx]);
	p->map.y_size = p->height - idx;
	p->map.x_size = find_x_size(p->map.y_size, tmp);
	i = 0;
	while (i < p->map.y_size)
	{
		tmp_x_size = (int)ft_strlen(tmp[i]);
		if (tmp_x_size < p->map.x_size)
			tmp[i] = replace_field(tmp[i], p->map.x_size, tmp_x_size);
		i++;
	}
	p->map.field = tmp;
}
