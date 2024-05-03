/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:24:03 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/03 16:31:31 by mkulikov         ###   ########.fr       */
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
