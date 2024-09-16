/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:29:13 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/16 15:16:54 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_if_quotes(char *value)
{
	int	i;

	i = 0;
	if (value[i] == SINGLE_QUOTE && value[ft_strlen(value) - 1] == SINGLE_QUOTE)
		return (1);
	else if (value[i] == DOUBLE_QUOTE 
		&& value[ft_strlen(value) - 1] == DOUBLE_QUOTE)
		return (2);
	while (value[i])
	{
		if (value[i] == SINGLE_QUOTE || value[i] == DOUBLE_QUOTE)
			return (3);
		i++;
	}
	return (0);
}

/* void	test_tokens(t_token *tokens)
{
	while (tokens != NULL)
	{
		printf("index: %i\n", tokens->index);
		printf("join: %i\n", tokens->join);
		printf("quotes: %i\n", tokens->quotes);
		printf("value: [%s]\n", tokens->value);
		tokens = tokens->next;
	}

} */
