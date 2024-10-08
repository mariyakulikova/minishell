/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:14:22 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/12 20:31:46 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_data *data, char **cmd_tab)
{
	t_env_lst	*list;

	list = data->lst;
	if (cmd_tab[1] != NULL)
		return (err_msg("env: Take no arguments\n", 1));
	while (list != NULL)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (0);
}
