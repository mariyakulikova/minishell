/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin_idx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:54:45 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/12 20:38:30 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_builtin_idx(t_data *data, char *str)
{
	int		i;
	int		size;
	char	**names;

	i = -1;
	size = 7;
	names = data->builtin_name;
	while (++i < size)
	{
		if (ft_strcmp(str, *(names + i)) == 0)
			return (i);
	}
	return (-1);
}
