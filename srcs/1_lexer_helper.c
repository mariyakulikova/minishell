/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:08:53 by fjoestin          #+#    #+#             */
/*   Updated: 2024/06/02 19:05:14 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_processing(t_data *data, t_lexer_help *lh)
{
	int	i;
	
}

t_token	*token_new(char *prompt, int start, int end, int white)
{
	t_token	*new;
	
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		exit(EXIT_FAILURE);
	new->value = ft_substr(prompt, start, end);
	new->index = INT_MAX;
	new->quotes = INT_MAX;
	if (white == 0)
		new->join = 1;
	else
		new->join = 2;
	new->prev = NULL;
	new->next = NULL;
	new->type = NULL;
	return (new);
}
