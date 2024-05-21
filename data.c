/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:12:04 by fjoestin          #+#    #+#             */
/*   Updated: 2024/05/21 15:32:59 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data **data, char **envp)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_SUCCESS);
	ft_memset(*data, 0, sizeof(t_data));
	(*data)->lst = set_envp_lst(envp);
	if (!(*data)->lst)
	{
		free(data);
		exit(EXIT_SUCCESS);
	}
}