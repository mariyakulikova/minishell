/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:22:27 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/15 21:58:59 by mkulikov         ###   ########.fr       */
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

static char	**update_cmd(char **old_cmd, t_token *token)
{
	int		size;
	int		i;
	char	**new_cmd;

	size = td_tab_size(old_cmd);
	new_cmd = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_cmd)
		return (NULL);
	new_cmd[size + 1] = NULL;
	new_cmd[size] = token->value;
	i = -1;
	while (++i < size)
		new_cmd[i] = old_cmd[i];
	free(old_cmd);
	return (new_cmd);
}

int	parse_cmd(t_data *data)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = data->tokens;
	while (curr && i < data->cmd_size)
	{
		if (curr->type == STRING)
		{
			data->cmd_tab[i] = update_cmd(data->cmd_tab[i], curr);
			if (!data->cmd_tab[i])
				return (1);
		}
		else if (curr->type == PIPE)
			++i;
		curr = curr->next;
	}
	return (0);
}
