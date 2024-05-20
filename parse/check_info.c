/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:29:24 by erho              #+#    #+#             */
/*   Updated: 2024/05/20 16:52:32 by erho             ###   ########.fr       */
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

int	check_dup_path(t_play *p)
{
	int	idx;
	int	tmp;

	idx = 0;
	while (idx < 4)
	{
		if (p->images[idx].path == NULL)
			return (FALSE);
		tmp = idx + 1;
		while (tmp < 4)
		{
			if (p->images[tmp].path == NULL
				|| ft_strcmp(p->images[idx].path, p->images[tmp].path))
				return (FALSE);
			tmp++;
		}
		idx++;
	}
	return (TRUE);
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

void	is_valid_character(size_t start, t_play *p, size_t *idx)
{
	size_t	key_start;
	char	*id;

	if (ft_isalpha(p->origin[*idx]))
	{
		key_start = *idx;
		while (*idx < p->origin_len && ft_isalpha(p->origin[*idx]))
			(*idx)++;
		if (*idx - key_start >= 3)
			print_error(ERROR_INVALID_INFO);
		id = ft_substr(p->origin, key_start, *idx - key_start);
		printf("id: %s\n", id);
		check_id(id, p, idx);
		while (*idx < p->origin_len && p->origin[*idx] == ' ')
			(*idx)++;
		if (*idx < p->origin_len && p->origin[*idx] != '\n')
			print_error(ERROR_INVALID_INFO);
	}
	else if (ft_isdigit(p->origin[*idx]))
	{
		(void)start;
		is_valid_sequence(p);
		p->check_parsing = TRUE;
		// p->map.split_map = split_map(&(p->origin[*idx - diff]), '\n');
	}
}

void	is_valid_info(t_play *p)
{
	size_t	idx;
	size_t	start;

	idx = 0;
	p->origin_len = ft_strlen(p->origin);
	while (idx < p->origin_len)
	{
		while (idx < p->origin_len && p->origin[idx] == '\n')
			idx++;
		start = idx;
		while (idx < p->origin_len && p->origin[idx] == ' ')
			idx++;
		if (idx < p->origin_len && p->origin[idx] == '\n')
			continue ;
		is_valid_character(start, p, &idx);
		idx++;
	}
	if (p->check_parsing == FALSE || check_dup_path(p) == FALSE)
		print_error(ERROR_INVALID_INFO);
}
