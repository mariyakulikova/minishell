/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:14:22 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/12 16:22:36 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_data *data, char **cmd_tab)
{
	int	i;
	t_env_lst *list;
	(void)cmd_tab;
	i = get_builtin_index(data->cmd_tab, "env");
	list = data->lst;
	if (data->cmd_tab[i][1] != NULL)
	{
		write(2, "env: Take no arguments\n", 24); // env: %s(arg): No such file or directory
		return (-1);
	}
	while (list != NULL)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (0);
}
