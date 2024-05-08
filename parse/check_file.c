/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:27:17 by erho              #+#    #+#             */
/*   Updated: 2024/05/09 05:23:33 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_file_name(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (ERROR_FILE_NAME);
	if (file[len - 4] != '.')
		return (ERROR_FILE_NAME);
	if (file[len - 3] != 'c')
		return (ERROR_FILE_NAME);
	if (file[len - 2] != 'u')
		return (ERROR_FILE_NAME);
	if (file[len - 1] != 'b')
		return (ERROR_FILE_NAME);
	return (VALID);
}

void	is_valid_file(char *file, int fd)
{
	if (fd < 0)
		print_error(ERROR_INVALID_FILE);
	if (is_valid_file_name(file) == ERROR_FILE_NAME)
		print_error(ERROR_FILE_NAME);
}
