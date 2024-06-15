/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sewopark <sewopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:16:28 by erho              #+#    #+#             */
/*   Updated: 2024/06/20 21:44:47 by sewopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_error(int error_no)
{
	if (error_no == MEMORY)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("memory allocation failed\n", 2);
		exit(1);
	}
}
