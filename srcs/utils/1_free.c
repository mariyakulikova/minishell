/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:06:16 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/16 12:06:19 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_reprompt(t_data *data)
{
	if (data->cmd_tab != NULL)
		free_triple_tab(data->cmd_tab, data->cmd_size);
	free_tokens(data->tokens);
	data->tokens = NULL;
	data->cmd_tab = NULL;
	// free fd list
	free_llist(data->fd_list_tab, data->cmd_size);
	data->fd_list_tab = NULL;
	free(data->prompt);
	data->prompt = NULL;
	free(data->line);
	data->line = NULL;
	// free prompt and line
}

void	free_tokens(t_token *tokens)
{
	if (!tokens)
		return ;
	while (tokens->next != NULL)
	{
		tokens = tokens->next;
		free(tokens->prev->value);
		free(tokens->prev);
	}
	free(tokens->value);
	free(tokens->next);
	free(tokens);
}

void	free_llist(t_llist **fd_list_tab, int size)
{
	int		i;
	t_llist	*curr;
	t_llist	*prev;

	if (!fd_list_tab)
		return ;
	i = -1;
	while (++i < size)
	{
		curr = *(fd_list_tab + i);
		while (curr)
		{
			prev = curr;
			curr = curr->next;
			free(prev);
		}
		*(fd_list_tab + i) = NULL;
	}
	free(fd_list_tab);
}
