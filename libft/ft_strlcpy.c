/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:10:18 by mkulikov          #+#    #+#             */
/*   Updated: 2023/12/05 13:21:20 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < destsize)
		ft_memcpy(dest, src, srclen + 1);
	else if (destsize != 0)
	{
		ft_memcpy(dest, src, destsize - 1);
		*(dest + destsize - 1) = '\0';
	}
	return (srclen);
}
