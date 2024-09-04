/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:22:27 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/04 13:47:40 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	td_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		++i;
	return (i);
}

char	**update_cmd(char **old_cmd, t_token *token)
{
	int		size;
	int		i;
	char	**new_cmd;

	size = td_tab_size(old_cmd);
	new_cmd = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_cmd)
		return (NULL);
	new_cmd[size + 1] = NULL;
	new_cmd[size] = ft_strdup(token->value);
	i = -1;
	while (++i < size)
	{
		new_cmd[i] = ft_strdup(old_cmd[i]);
		free(old_cmd[i]);
	}
	free(old_cmd);
	return (new_cmd);
}
