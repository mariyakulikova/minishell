/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:04:18 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/13 14:31:30 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envp_lst_free(t_env_lst *lst)
{
	t_env_lst	*curr;
	t_env_lst	*prev;

	curr = lst;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		free(prev->key);
		free(prev->value);
		free(prev);
	}
}

t_env_lst	*envp_lst_new(char *envp)
{
	t_env_lst	*new;
	int			c;

	new = (t_env_lst *)malloc(sizeof(t_env_lst));
	if (!new)
		return (NULL);
	c = str_chr_idx(envp, '=');
	if (c > -1)
	{
		new->key = ft_substr(envp, 0, c);
		new->value = ft_substr(envp, c + 1, ft_strlen(envp) - c);
	}
	else
	{
		new->key = NULL;
		new->value = NULL;
	}
	new->next = NULL;
	// printf("envp_lst_new -----> %s = %s\n", new->key, new->value);
	return (new);
}

t_env_lst	*set_envp_lst(char **envp)
{
	t_env_lst	*head;
	t_env_lst	*curr;
	int			i;

	head = envp_lst_new(*envp);
	curr = head;
	i = 1;
	while (*(envp + i))
	{
		curr->next = envp_lst_new(*(envp + i));
		if (!curr->next)
		{
			envp_lst_free(head);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	return (head);
}

t_env_lst	*get_var_by_key(t_env_lst *envp_list, char *key)
{
	t_env_lst	*curr;

	curr = envp_list;
	while (curr)
	{
		if (ft_strcmp((char *)curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
