/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:13:53 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/14 16:57:22 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	remove_from_list(t_env_lst *envlst, char *keyvar);

int	ft_unset(t_data *data, char **cmd_tab)
{
	int	wunset;
	int	idx;

	(void)cmd_tab;
	wunset = get_builtin_index(data->cmd_tab, "unset");
	idx = 1;
	if (data->cmd_tab[wunset][idx] == NULL)
		return (0);
	
	while (data->cmd_tab[wunset][idx])
	{
		while (ft_strcmp(data->cmd_tab[wunset][idx], "_") == 0)
			idx++;
		if (ft_strcmp(data->cmd_tab[wunset][idx], "SHELL") == 0)
			return (0);
		remove_from_list(data->lst, data->cmd_tab[wunset][idx]);
		remove_from_list(data->export_list, data->cmd_tab[wunset][idx]);
		idx++;
	}
	return (0);
}

static void	remove_from_list(t_env_lst *envlst, char *keyvar)
{
	t_env_lst	*tmp;

	tmp = envlst;
	while (envlst != NULL)
	{
		if (ft_strcmp(envlst->key, keyvar) == 0)
		{
			tmp->next = envlst->next;
			free(envlst->key);
			if (envlst->value != NULL)
				free(envlst->value);
			free(envlst);
			envlst = tmp;
		}
		tmp = envlst;
		envlst = envlst->next;
	}
}
