/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:29:13 by fjoestin          #+#    #+#             */
/*   Updated: 2024/08/21 16:20:27 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_if_quotes(char *value)
{
	int	i;

	i = 0;
	if (value[i] == SINGLE_QUOTE && value[ft_strlen(value) - 1] == SINGLE_QUOTE)
		return (1);
	else if (value[i] == DOUBLE_QUOTE && value[ft_strlen(value) - 1] ==DOUBLE_QUOTE)
		return (2);
	while (value[i])
	{
		if (value[i] == SINGLE_QUOTE || value[i] == DOUBLE_QUOTE)
			return (3);
		i++;
	}
	return (0);
}

/* t_type	get_type() */