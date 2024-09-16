/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:24:57 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/16 12:04:34 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_exp_list(t_env_lst *curr, char *new_key, char *new_value)
{
	bool		found;
	t_env_lst	*new;
	t_env_lst	*tmp;

	found = false;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->key, new_key) == 0)
		{
			found = true;
			if (new_value != NULL)
			{
				free(curr->value);
				curr->value = ft_substr(new_value, 0, ft_strlen(new_value));
			}
		}
		tmp = curr;
		curr = curr->next;
	}
	if (found == false)
	{
		new = new_env(new_key, new_value);
		tmp->next = new;
	}
}

t_env_lst	*new_env(char *new_key, char *new_value)
{
	t_env_lst	*new;

	new = (t_env_lst *)malloc(sizeof(t_env_lst));
	if (!new)
		perror("Error malloc\n");
	new->key = ft_substr(new_key, 0, ft_strlen(new_key));
	if (new_value != NULL)
		new->value = ft_substr(new_value, 0, ft_strlen(new_value));
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}
