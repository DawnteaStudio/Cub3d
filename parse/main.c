/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:07:53 by erho              #+#    #+#             */
/*   Updated: 2024/05/20 16:31:58 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*read_map(char *map_file)
{
	t_fopen	fopen;
	int		fd;
	char	*result;

	result = (char *)malloc(sizeof(char) * 1);
	if (result == NULL)
		ft_error(MEMORY);
	result[0] = '\0';
	fd = open(map_file, O_RDONLY);
	is_valid_file(map_file, fd);
	while (1)
	{
		fopen.buff = get_next_line(fd);
		if (fopen.buff == NULL)
			break ;
		else
		{
			fopen.read_size = ft_strlen(fopen.buff);
			result = gnl_strjoin(&result, fopen);
			free(fopen.buff);
		}
	}
	return (result);
}

int	main(int argc, char **argv)
{
	t_play	play;

	if (argc != 2)
		print_error(ERROR_STANDARD_INPUT);
	initial_play(&play);
	play.origin = read_map(argv[1]);
	if (play.origin[0] == '\0')
		print_error(ERROR_INVALID_FILE);
	is_valid_info(&play);
	//game(&play);
	return (0);
}
