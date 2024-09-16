/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:56:23 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/16 13:17:49 by fjoestin         ###   ########.fr       */
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

char	**ft_split_red_ms(char *prompt, int wred)
{
	int		size;
	char	**split;

	if (wred != 0 && prompt[wred + 1] != '\0')
		size = 3;
	else
		size = 2;
	split = (char **)malloc(sizeof(char *) * (size + 1));
	if (wred == 0)
	{
		split[0] = ft_substr(prompt, 0, 1);
		split[1] = ft_substr(prompt, (wred + 1), (ft_strlen(prompt) - wred));
	}
	else
	{
		split[0] = ft_substr(prompt, 0, wred);
		split[1] = ft_substr(prompt, wred, 1);
		if (size == 3)
			split[2] = ft_substr(prompt, (wred + 1),
					(ft_strlen(prompt) - wred));
	}
	split[size] = NULL;
	return (split);
}

void	check_types(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	while (token != NULL)
	{
		if (token->type == PIPE && (token->index == 0
				|| token->index == (data->n_tokens - 1)))
			ft_exit_err("pipe doesn't work\n", data);
		if (token->type != STRING && ((token->index == 0
					&& (data->n_tokens == 1))
				|| token->index == (data->n_tokens - 1)))
			ft_exit_err("unexpected syntax\n", data);
		if (token->type == PIPE && token->next->type == PIPE)
			ft_exit_err("2 pipes\n", data);
		if ((token->type != STRING && token->type != PIPE)
			&& token->next->type != STRING)
			ft_exit_err("unexpected syntax\n", data);
		token = token->next;
	}
}
