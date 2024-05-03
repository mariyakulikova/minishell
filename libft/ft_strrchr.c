/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:43:33 by mkulikov          #+#    #+#             */
/*   Updated: 2023/11/17 15:28:21 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*ptr;

	ptr = (char *)s;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (*(ptr + len) == (char)c)
			return (ptr + len);
		len--;
	}
	return (NULL);
}
