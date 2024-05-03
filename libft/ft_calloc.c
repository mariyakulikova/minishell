/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:39:24 by mkulikov          #+#    #+#             */
/*   Updated: 2023/11/24 17:35:57 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	size_t	size;
	void	*ptr;

	size = nelem * elsize;
	if (elsize && ((size / elsize) != nelem))
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}
