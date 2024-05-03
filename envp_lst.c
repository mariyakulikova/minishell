/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:04:18 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/03 14:32:43 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp_lst	*envp_lst_new(char *key, char *value)
{
	t_envp_lst	*new;

	new = (t_envp_lst *)malloc(sizeof(t_envp_lst));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_envp_lst	*set_envp_lst(char **envp)
{
	t_envp_lst	*lst;
	int			c;
	char		*key;
	char		*value;

	lst = NULL;
	while (*envp)
	{
		// c = ft_strchr(*envp, '=');
		// key = ft_substr()
		// envp++;
	}
	return (lst);
}
