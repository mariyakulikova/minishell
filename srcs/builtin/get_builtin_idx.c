/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin_idx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:54:45 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/18 13:56:25 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_builtin_idx(t_data *data)
{
	int		i;
	int		size;
	char	*prompt;
	char	**names;

	i = 0;
	size = 7;
	prompt = data->prompt;
	names = data->builtin_name;
	while (i < size)
	{
		if (ft_strcmp(prompt, names[i]) == 0)
			return(i);
		i++;
	}
	return (-1);
}
