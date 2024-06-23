/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:27:17 by erho              #+#    #+#             */
/*   Updated: 2024/06/23 14:59:32 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	is_valid_file_name(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (ERROR_FILE_NAME);
	if (ft_strcmp(&file[len - 4], ".cub") != 0)
		print_error(ERROR_INVALID_INFO);
	return (VALID);
}

void	is_valid_file(char *file, int fd)
{
	if (fd < 0)
		print_error(ERROR_INVALID_FILE);
	if (is_valid_file_name(file) == ERROR_FILE_NAME)
		print_error(ERROR_FILE_NAME);
}
