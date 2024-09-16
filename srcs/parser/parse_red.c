/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:22:27 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/16 11:59:53 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_fd_list(t_llist **fd_list, t_token **curr)
{
	t_llist	*new;

	if ((*curr)->next == NULL)
		return (1);
	new = new_llist((void *)&(*curr)->type, (void *)(*curr)->next->value);
	if (!new)
		return (1);
	(*curr) = (*curr)->next;
	llistadd_back(fd_list, new);
	return (0);
}

bool	is_red(t_token *token)
{
	if (token->type == RED_OUT || token->type == APPEND || \
		token->type == RED_IN || token->type == HERE_DOC)
		return (true);
	return (false);
}
