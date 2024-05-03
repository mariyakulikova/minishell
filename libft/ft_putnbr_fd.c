/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:04:48 by mkulikov          #+#    #+#             */
/*   Updated: 2023/11/17 17:36:14 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	long	nbr;
	char	arr[10];

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	nbr = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
	}
	i = 0;
	while (nbr > 0)
	{
		arr[i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	while (--i >= 0)
	{
		ft_putchar_fd(arr[i], fd);
	}
}
