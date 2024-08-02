/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:29:13 by fjoestin          #+#    #+#             */
/*   Updated: 2024/08/02 16:04:28 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_if_quotes(char *value)
{
	int	i;

	i = 0;
	if (value[i] == SINGLE_QUOTE)
		return (1);
	if (value[i] == DOUBLE_QUOTE)
		return (2);
	return (0);
}

/* t_type	get_type() */