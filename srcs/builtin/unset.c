/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:13:53 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/06 22:56:27 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	remove_from_list(t_env_lst *envlst, char *keyvar);

int	ft_unset(t_data *data)
{
	int	wunset;
	int	idx;

	wunset = get_builtin_index(data->cmd_tab, "unset");
	idx = 1;
	if (data->cmd_tab[wunset][idx] == NULL)
		return (0);
	while (data->cmd_tab[wunset][idx])
	{
		while (ft_strcmp(data->cmd_tab[wunset][idx], "_") == 0)
			idx++;
		remove_from_list(data->lst, data->cmd_tab[wunset][idx]);
		remove_from_list(data->export_list, data->cmd_tab[wunset][idx]);
		idx++;
	}
	//test_list(data->export_list);
	return (0);
}

static void	remove_from_list(t_env_lst *envlst, char *keyvar)
{
	t_env_lst	*tmp;

	tmp = NULL;
	while (envlst->next != NULL)
	{
		if (ft_strcmp(envlst->next->key, keyvar) == 0)
		{
			tmp = envlst->next->next;
			free(envlst->next->key);
			free(envlst->next->value);
			free(envlst->next);
			envlst->next = tmp;
		}
		envlst = envlst->next;
	}
}