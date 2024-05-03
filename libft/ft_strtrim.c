/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:16:57 by mkulikov          #+#    #+#             */
/*   Updated: 2023/11/24 15:59:21 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_new_str(char const *s, int start, int end)
{
	int		len;
	char	*str;

	len = end - start;
	if (len < 0)
		len = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	*(str + len) = '\0';
	while (--len >= 0)
		*(str + len) = *(s + start + len);
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*chr;
	char	*str;

	start = 0;
	end = ft_strlen(s1);
	chr = ft_strchr(set, *s1);
	while (chr)
	{
		start++;
		chr = ft_strchr(set, *(s1 + start));
	}
	chr = ft_strchr(set, *(s1 + --end));
	while (chr)
	{
		end--;
		chr = ft_strchr(set, *(s1 + end));
	}
	str = get_new_str(s1, start, end + 1);
	return (str);
}
