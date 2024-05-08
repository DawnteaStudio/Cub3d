/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:29:24 by erho              #+#    #+#             */
/*   Updated: 2024/05/09 06:03:41 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_id(char *id, t_play *p, size_t *idx)
{
	if (ft_strcmp(id, "NO") == 0)
		extract_path(p, idx, NORTH);
	else if (ft_strcmp(id, "SO") == 0)
		extract_path(p, idx, SOUTH);
	else if (ft_strcmp(id, "WE") == 0)
		extract_path(p, idx, WEST);
	else if (ft_strcmp(id, "EA") == 0)
		extract_path(p, idx, EAST);
	else if (ft_strcmp(id, "F") == 0)
		extract_color(p, p->map.floor, idx);
	else if (ft_strcmp(id, "C") == 0)
		extract_color(p, p->map.ceiling, idx);
	else
		print_error(ERROR_INVALID_INFO);
}

void	is_valid_sequence(t_play *p)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (p->images[i].path == NULL)
			print_error(ERROR_INVALID_INFO);
		i++;
	}
	if (p->map.ceiling[0] == -1 || p->map.floor[0] == -1)
		print_error(ERROR_INVALID_INFO);
}

void	is_valid_character(size_t diff, t_play *p, size_t *idx)
{
	size_t	start;
	char	*id;

	if (diff == 0 && ft_isalpha(p->origin[*idx]))
	{
		start = *idx;
		while (*idx < p->origin_len && ft_isalpha(p->origin[*idx]))
			(*idx)++;
		if (*idx - start >= 3)
			print_error(ERROR_INVALID_INFO);
		id = ft_substr(p->origin, start, *idx - start);
		check_id(id, p, idx);
	}
	else if (diff != 0 && ft_isdigit(p->origin[*idx]))
	{
		is_valid_sequence(p);
		// p->map.split_map = split_map(&(p->origin[*idx - diff]), '\n');
	}
}

void	is_valid_info(t_play *p)
{
	size_t	idx;
	size_t	start;

	idx = 0;
	p->origin_len = ft_strlen(p->origin);
	if (p->origin[0] == '\n' || p->origin[p->origin_len - 1] == '\n')
		print_error(ERROR_INVALID_INFO);
	while (idx < p->origin_len)
	{
		while (idx < p->origin_len && p->origin[idx] == '\n')
			idx++;
		start = idx;
		while (idx < p->origin_len && p->origin[idx] == ' ')
			idx++;
		is_valid_character(idx - start, p, &idx);
		idx++;
	}
}
