/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erho <erho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:00:21 by erho              #+#    #+#             */
/*   Updated: 2024/05/08 23:36:50 by erho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	make_word(char *s1, char const *s2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

int	count_word(char const *s, char c)
{
	int	i;
	int	cnt;
	int	next_line;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		next_line = 0;
		while (s[i + next_line] && s[i + next_line] == c)
			next_line++;
		if (next_line >= 2)
			print_error(ERROR_INVALID_MAP);
		else
			i += next_line;
		if (s[i])
			cnt++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (cnt);
}

char	**ft_insert(char const *s, char **res, char c)
{
	int	i;
	int	word;
	int	array;

	i = 0;
	array = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		word = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > word)
		{
			res[array] = (char *)malloc(sizeof(char) * (i - word + 1));
			if (res[array] == NULL)
				ft_error(MEMORY);
			make_word(res[array], &s[word], i - word);
			array++;
		}
	}
	return (res);
}

char	**split_map(char const *s, char c)
{
	int		cnt;
	char	**res;

	cnt = count_word(s, c);
	res = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (res == NULL)
		ft_error(MEMORY);
	res = ft_insert(s, res, c);
	if (res != NULL)
		res[cnt] = NULL;
	return (res);
}
