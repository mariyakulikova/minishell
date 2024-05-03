/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:29:16 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/03 16:31:07 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_init(t_data **data, char **envp)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_SUCCESS);
	ft_memset(*data, 0, sizeof(t_data));
	(*data)->lst = set_env_lst(envp);
	if (!(*data)->lst)
	{
		free(data);
		exit(EXIT_SUCCESS);
	}
}
