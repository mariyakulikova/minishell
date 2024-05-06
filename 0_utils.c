/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:24:03 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/06 13:06:12 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_chr_idx(const char *str, int c)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\f' || \
		c == '\n' || c == '\r' || \
		c == '\t' || c == '\v')
		return (1);
	return (0);
}
