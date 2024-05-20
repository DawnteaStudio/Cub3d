/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:13:08 by erho              #+#    #+#             */
/*   Updated: 2024/05/20 16:33:19 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	extract_path(t_play *p, size_t *idx, int image_type)
{
	size_t	start;
	char	*tmp;
	size_t	path_len;

	if (p->images[image_type].path != NULL)
		print_error(ERROR_INVALID_INFO);
	start = *idx;
	while (*idx < p->origin_len && p->origin[*idx] == ' ')
		(*idx)++;
	if (*idx == start)
		print_error(ERROR_INVALID_INFO);
	start = *idx;
	while (*idx < p->origin_len && p->origin[*idx] != ' '
		&& p->origin[*idx] != '\n')
		(*idx)++;
	path_len = *idx - start;
	if (path_len < 4)
		print_error(ERROR_INVALID_INFO);
	p->images[image_type].path = ft_substr(p->origin, start, *idx - start);
	tmp = p->images[image_type].path;
	if (ft_strcmp(&tmp[path_len - 4], ".xpm") != 0)
		print_error(ERROR_INVALID_INFO);
	printf("path: %s\n", p->images[image_type].path);
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

int	find_number(t_play *p, size_t *idx)
{
	size_t	start;
	char	*tmp;
	int		res;

	start = *idx;
	while (*idx < p->origin_len && p->origin[*idx] != '\n'
			&& p->origin[*idx] != ',' && p->origin[*idx] != ' ')
		(*idx)++;
	tmp = ft_substr(p->origin, start, *idx - start);
	res = check_number(tmp);
	return (res);
}

void	extract_color(t_play *p, int *arr, size_t *idx)
{
	size_t	start;
	int		arr_idx;

	arr_idx = 0;
	if (arr[0] != -1)
		print_error(ERROR_INVALID_INFO);
	start = *idx;
	while (*idx < p->origin_len && p->origin[*idx] == ' '
			&& p->origin[*idx] != '\n')
		(*idx)++;
	if (*idx == start)
		print_error(ERROR_INVALID_INFO);
	while (*idx < p->origin_len && p->origin[*idx] != ' '
		&& p->origin[*idx] != '\n')
	{
		if (arr_idx == 3)
			print_error(ERROR_INVALID_INFO);
		arr[arr_idx++] = find_number(p, idx);
		if (*idx < p->origin_len && p->origin[*idx] != '\n')
			(*idx)++;
	}
	if (arr_idx < 3)
		print_error(ERROR_INVALID_INFO);
	printf("color: %d, %d, %d\n", arr[0], arr[1], arr[2]);
}
