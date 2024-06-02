/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:07:53 by erho              #+#    #+#             */
/*   Updated: 2024/06/02 19:01:51 by erho             ###   ########.fr       */
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

char	**join_exp(char **exp, char *str, size_t *height)
{
	char	**new_exp;
	size_t	i;
	size_t	len;

	new_exp = set_exp(*height + 1);
	i = 0;
	while (i < *height)
	{
		new_exp[i] = exp[i];
		i++;
	}
	len = ft_strlen(str);
	new_exp[i] = ft_substr(str, 0, len - 1);
	free(exp);
	free(str);
	(*height)++;
	return (new_exp);
}

char	**read_map(size_t *height, char *map_file)
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

void	set_height(t_play *p)
{
	size_t	i;
	size_t	width;

	i = p->height - 1;
	while (i >= 0) {
		width = 0;
		while (p->origin[i][width] == ' ')
			width++;
		if (p->origin[i][width] != '\0')
		{
			p->height = i + 1;
			break ;
		}
		i--;
	}
}

int	main(int argc, char **argv)
{
	t_play	play;

	if (argc != 2)
		print_error(ERROR_STANDARD_INPUT);
	initial_play(&play);
	play.origin = read_map(&(play.height), argv[1]);
	if (play.origin[0] == NULL)
		print_error(ERROR_INVALID_FILE);
	set_height(&play);
	is_valid_info(&play);
	//game(&play);
	return (0);
}
