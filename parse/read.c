/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:16:24 by erho              #+#    #+#             */
/*   Updated: 2024/06/04 16:13:16 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**set_exp(int size)
{
	char	**res;

	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		ft_error(MEMORY);
	res[size] = NULL;
	return (res);
}

char	**join_exp(char **exp, char *str, int *height)
{
	char	**new_exp;
	int		i;
	int		len;

	new_exp = set_exp(*height + 1);
	i = 0;
	while (i < *height)
	{
		new_exp[i] = exp[i];
		i++;
	}
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		len--;
	new_exp[i] = ft_substr(str, 0, len);
	free(exp);
	free(str);
	(*height)++;
	return (new_exp);
}

char	**read_map(int *height, char *map_file)
{
	char	*buff;
	int		fd;
	char	**result;

	result = set_exp(0);
	fd = open(map_file, O_RDONLY);
	is_valid_file(map_file, fd);
	while (1)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		else
			result = join_exp(result, buff, height);
	}
	return (result);
}
