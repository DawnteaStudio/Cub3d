/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:29:24 by erho              #+#    #+#             */
/*   Updated: 2024/06/02 20:04:26 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_id(char *id, t_play *p, size_t idx, size_t *width)
{
	if (ft_strcmp(id, "NO") == 0)
		extract_path(p, idx, width, NORTH);
	else if (ft_strcmp(id, "SO") == 0)
		extract_path(p, idx, width, SOUTH);
	else if (ft_strcmp(id, "WE") == 0)
		extract_path(p, idx, width, WEST);
	else if (ft_strcmp(id, "EA") == 0)
		extract_path(p, idx, width, EAST);
	else if (ft_strcmp(id, "F") == 0)
		extract_color(p, p->map.floor, idx, width);
	else if (ft_strcmp(id, "C") == 0)
		extract_color(p, p->map.ceiling, idx, width);
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
				|| ft_strcmp(p->images[idx].path, p->images[tmp].path) == 0)
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

void	is_valid_character(size_t idx, size_t width, t_play *p)
{
	size_t	key_start;
	char	*id;

	if (ft_isalpha(p->origin[idx][width]))
	{
		key_start = width;
		while (ft_isalpha(p->origin[idx][width]))
			width++;
		if (width - key_start >= 3 || p->origin[idx][width] != ' ')
			print_error(ERROR_INVALID_INFO);
		id = ft_substr(p->origin[idx], key_start, width - key_start);
		check_id(id, p, idx, &width);
		while (p->origin[idx][width] == ' ')
			width++;
		if (p->origin[idx][width] != '\0')
			print_error(ERROR_INVALID_INFO);
	}
	else if (ft_isdigit(p->origin[idx][width]))
	{
		is_valid_sequence(p);
		p->check_parsing = TRUE;
		p->map.field = &(p->origin[idx]);
		p->map.y_size = p->height - idx;
		//is_valid_map(&(p->map));
	}
}

void	is_valid_info(t_play *p)
{
	size_t	idx;
	size_t	width;

	idx = 0;
	while (p->origin[idx])
	{
		while (p->origin[idx] && p->origin[idx][0] == '\0')
			idx++;
		if (p->origin[idx] == NULL)
			break ;
		width = 0;
		while (p->origin[idx][width] == ' ')
			width++;
		if (p->origin[idx][width] != '\0')
			is_valid_character(idx, width, p);
		idx++;
	}
	if (p->check_parsing == FALSE || check_dup_path(p) == FALSE)
		print_error(ERROR_INVALID_INFO);
}
