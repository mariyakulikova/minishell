/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:56:23 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/14 02:11:16 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_new_token(char *line, t_token **curr)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->value = ft_strdup(line);
	new->index = INT_MAX;
	new->join = TRUE;
	new->quotes = get_if_quotes(new->value);
	new->type = STRING;
	new->prev = *curr;
	if ((*curr)->next)
	{
		new->next = (*curr)->next;
		(*curr)->next->prev = new;
	}
	else
		new->next = NULL;
	return (new);
}
