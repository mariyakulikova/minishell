/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:05:45 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/14 01:47:45 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	lexer(t_data *data)
{
	if (!check_open_quotes(data->prompt))
		return (perror("Error: not all quotes were closed"), 1); //!
	data->tokens = tokenizer(data);
	processing(data);
	expander(data->tokens, data);
	remove_empty_tokens(data);
	if (data->n_tokens == 0)
		ft_exit_err(NULL, data);
	return (0);
}

bool	check_open_quotes(char *prompt)
{
	bool	in_single;
	bool	in_double;
	int		i;

	in_double = false;
	in_single = false;
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (prompt[i] == '\'' && !in_double)
			in_single = !in_single;
		i++;
	}
	return (!in_double && !in_single);
}

void	processing(t_data *data)
{
	update_type(data);
	update_index(data->tokens, data);
	check_types(data);
}

void	update_index(t_token *tokens, t_data *data)
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		tokens->index = i;
		i++;
		tokens = tokens->next;
	}
	data->n_tokens = i;
}

void	update_type(t_data *data)//**
{
	t_token	*tokens;
	int		i;

	tokens = data->tokens;
	i = 0;
	while (tokens != NULL)
	{
		i = 0;
		while (tokens->value[i] != '\0')
		{
			if (tokens->value[i] == PIPE_PROMPT)
			{
				tokens->type = check_pipe(tokens, data);
				break ;
			}
			if (tokens->value[i] == '<' || tokens->value[i] == '>')
			{
				tokens->type = check_redirect(tokens, data);
				break ;
			}
			i++;
		}
		tokens = tokens->next;
	}
}

