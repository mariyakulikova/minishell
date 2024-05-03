/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:21:48 by mkulikov          #+#    #+#             */
/*   Updated: 2023/11/24 13:07:19 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrdst;
	unsigned char	*ptrsrc;

	ptrdst = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	if (!ptrdst && !ptrsrc)
		return (NULL);
	while (n > 0)
	{
		*ptrdst = *ptrsrc;
		ptrdst++;
		ptrsrc++;
		n--;
	}
	return (dest);
}
