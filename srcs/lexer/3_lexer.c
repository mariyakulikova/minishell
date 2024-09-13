/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:30:54 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/12 17:33:42 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*remove_token(t_token *curr, t_data *data)
{
	t_token	*temp;

	if (curr->prev)
	{
		temp = curr->prev;
		if(curr->next)
		{
			curr->next->prev = temp;
			temp->next = curr->next;
		}
		else
			temp->next = NULL;
		free(curr->value);
		free(curr);
		return (temp);
	}
	data->tokens = curr->next;
	if (data->tokens)
		data->tokens->prev = NULL;
	free(curr->value);
	free(curr);
	return (data->tokens);
}

void	remove_empty_tokens(t_data *data)
{
	t_token	*curr;

	curr = data->tokens;
	while (curr)
	{
		if (curr->value[0] == '\0')
		{
			curr = remove_token(curr, data);
			data->n_tokens -= 1;
		}
		else
			curr = curr->next;
	}
	update_index(data->tokens, data);
}
