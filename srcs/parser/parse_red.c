/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:22:27 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/21 10:54:15 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int get_stream_type(t_type type)
{
	if (type == RED_OUT || type == APPEND)
		return (1);
	return (0);
}

static int	add_fd_list(t_llist **fd_list, t_token **curr)
{
	t_llist	*new;
	int		stream_type;

	if ((*curr)->next == NULL)
		return (1);
	stream_type = get_stream_type((*curr)->type);
	new = new_llist((void *)(*curr)->type, (void *)(*curr)->next->value);
	if (!new)
		return (1);
	(*curr) = (*curr)->next;
	llistadd_back(fd_list + stream_type, new);
	return (0);
}

static bool	is_red(t_token *token)
{
	if (token->type == RED_OUT || token->type == APPEND || \
		token->type == RED_IN || token->type == HERE_DOC)
		return (true);
	return (false);
}

int	parse_red(t_data *data)
{
	t_token	*curr;
	int		i;

	curr = data->tokens;
	i = 0;
	while (curr && i < data->cmd_size)
	{
		if (is_red(curr))
		{
			if (add_fd_list(data->fd_list_tab + i, &curr))
				return (1);
		}
		else if (curr->type == PIPE)
			++i;
		curr = curr->next;
	}
	return (0);
}
