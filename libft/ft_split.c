/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:21:13 by mkulikov          #+#    #+#             */
/*   Updated: 2024/02/22 12:03:41 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(char const *s, char c)
{
	size_t	counter;
	size_t	j;

	counter = 0;
	while (*s)
	{
		j = 0;
		if (*s != c)
		{
			counter++;
			while (*(s + j) && *(s + j) != c)
				j++;
			s += j;
		}
		else
			s++;
	}
	return (counter);
}

static size_t	word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static void	ultimate_free(char **arr, size_t idx)
{
	while (idx > 0)
	{
		idx--;
		free(*(arr + idx));
	}
	free(arr);
}

static char	**get_array(char **arr, char const *s, size_t size, char c)
{
	size_t	i;
	size_t	len;

	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		while (*s && *s == c)
			s++;
		len = word_len(s, c);
		*(arr + i) = ft_substr(s, 0, len);
		if (!*(arr + i))
		{
			ultimate_free(arr, i);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
		i++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	arr = get_array(arr, s, size, c);
	if (!arr)
		return (NULL);
	*(arr + size) = NULL;
	return (arr);
}
