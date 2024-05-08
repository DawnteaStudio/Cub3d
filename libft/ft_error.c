/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:16:28 by erho              #+#    #+#             */
/*   Updated: 2024/05/08 20:24:42 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_error(int error_no)
{
	if (error_no == MEMORY)
	{
		ft_putstr_fd("memory allocation failed\n", 2);
		exit(1);
	}
	else
	{
		ft_putstr_fd("overflow occured\n", 2);
		exit(1);
	}
}
