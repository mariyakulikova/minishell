/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:30:53 by mkulikov          #+#    #+#             */
/*   Updated: 2023/11/20 14:30:23 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(int n)
{
	size_t	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	size_t		len;
	long		nbr;

	nbr = n;
	len = get_len(n);
	if (n < 0)
		nbr *= -1;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	*(ptr + len) = '\0';
	while (len--)
	{
		*(ptr + len) = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		*ptr = '-';
	return (ptr);
}
