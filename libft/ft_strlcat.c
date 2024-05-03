/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:00:04 by mkulikov          #+#    #+#             */
/*   Updated: 2023/11/27 14:21:18 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	destlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (!dest && !destsize)
		return (srclen);
	destlen = ft_strlen(dest);
	if (destlen >= destsize)
		return (srclen + destsize);
	else
		destsize -= destlen;
	ft_strlcpy(dest + destlen, src, destsize);
	return (destlen + srclen);
}
