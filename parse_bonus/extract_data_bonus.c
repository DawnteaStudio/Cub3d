/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:13:08 by erho              #+#    #+#             */
/*   Updated: 2024/06/23 14:59:41 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	extract_path(t_play *p, int idx, int *width, int image_type)
{
	int		start;
	char	*tmp;
	int		path_len;

	if (p->images[image_type].path != NULL)
		print_error(ERROR_INVALID_INFO);
	while (p->origin[idx][*width] == ' ')
		(*width)++;
	if (p->origin[idx][*width] == '\0')
		print_error(ERROR_INVALID_INFO);
	start = *width;
	while (p->origin[idx][*width] != ' ' && p->origin[idx][*width])
		(*width)++;
	path_len = *width - start;
	if (path_len < 4)
		print_error(ERROR_INVALID_INFO);
	p->images[image_type].path = ft_substr(p->origin[idx], start, path_len);
	tmp = p->images[image_type].path;
	if (ft_strcmp(&tmp[path_len - 4], ".xpm") != 0)
		print_error(ERROR_INVALID_INFO);
}

int	check_number(char *tmp)
{
	int	i;
	int	res;

	i = 0;
	while (tmp[i])
	{
		if (ft_isdigit(tmp[i]) == FALSE)
			print_error(ERROR_INVALID_INFO);
		i++;
	}
	res = ft_atoi(tmp);
	if (0 > res || res > 255)
		print_error(ERROR_INVALID_INFO);
	free(tmp);
	return (res);
}

int	find_number(t_play *p, int idx, int *width)
{
	int		start;
	char	*tmp;
	int		res;

	start = *width;
	while (p->origin[idx][*width] && p->origin[idx][*width] != ','
		&& p->origin[idx][*width] != ' ')
		(*width)++;
	if (start == *width)
		print_error(ERROR_INVALID_INFO);
	tmp = ft_substr(p->origin[idx], start, *width - start);
	res = check_number(tmp);
	return (res);
}

void	extract_color(t_play *p, int *arr, int idx, int *width)
{
	int	arr_idx;

	arr_idx = 0;
	if (arr[0] != -1)
		print_error(ERROR_INVALID_INFO);
	while (p->origin[idx][*width] == ' ')
		(*width)++;
	if (p->origin[idx][*width] == '\0')
		print_error(ERROR_INVALID_INFO);
	while (p->origin[idx][*width] != ' ' && p->origin[idx][*width])
	{
		if (arr_idx == 3)
			print_error(ERROR_INVALID_INFO);
		arr[arr_idx++] = find_number(p, idx, width);
		if (p->origin[idx][*width])
			(*width)++;
	}
	if (arr_idx < 3)
		print_error(ERROR_INVALID_INFO);
}
