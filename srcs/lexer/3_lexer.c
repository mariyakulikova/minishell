/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:30:54 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/17 12:38:31 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*remove_token(t_token *curr, t_data *data)
{
	t_token	*temp;

	if (curr->prev)
	{
		temp = curr->prev;
		if (curr->next)
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
		if (curr->value[0] == '\0' && curr->quotes == 0)
		{
			curr = remove_token(curr, data);
			data->n_tokens -= 1;
		}
		else
			curr = curr->next;
	}
	update_index(data->tokens, data);
}

int	check_word(char *prompt)
{
	int		i;
	bool	ins_quotes;
	bool	ind_quotes;

	i = 0;
	ins_quotes = false;
	ind_quotes = false;
	while (prompt[i] != '\0')
	{
		if (prompt[i] == SINGLE_QUOTE && !ind_quotes)
			ins_quotes = !ins_quotes;
		else if (prompt[i] == DOUBLE_QUOTE && !ins_quotes)
			ind_quotes = !ind_quotes;
		if (is_space(prompt[i + 1]) && ind_quotes == false
			&& ins_quotes == false)
			return (++i);
		i++;
	}
	return (i);
}

t_type	check_pipe(t_token *tokens, t_data *data)
{
	int		i;
	bool	in_squotes;
	bool	in_dquotes;

	i = 0;
	in_squotes = false;
	in_dquotes = false;
	if (tokens->value[0] == PIPE_PROMPT && tokens->value[1] == '\0')
		return (PIPE);
	while (tokens->value[i])
	{
		if (tokens->value[i] == SINGLE_QUOTE && !in_dquotes)
			in_squotes = !in_squotes;
		else if (tokens->value[i] == DOUBLE_QUOTE && !in_squotes)
			in_dquotes = !in_dquotes;
		if (tokens->value[i] == PIPE_PROMPT && !in_squotes && !in_dquotes)
		{
			real_pipe(tokens, data);
			break ;
		}
		i++;
	}
	if (tokens->value[0] == PIPE_PROMPT && tokens->value[1] == '\0')
		return (PIPE);
	return (STRING);
}

void	real_pipe(t_token *token, t_data *data)
{
	char	**split;
	int		wpipe;
	int		j;
	t_token	*tmp;

	wpipe = str_chr_idx(token->value, PIPE_PROMPT);
	split = ft_split_red_ms(token->value, wpipe);
	free(token->value);
	token->value = ft_strdup(split[0]);
	j = 1;
	while (split[j] && token != NULL)
	{
		tmp = ft_new_token(split[j], &token);
		token->next = tmp;
		if (token->next)
			token = token->next;
		j++;
	}
	free_split(split);
	processing(data);
}
