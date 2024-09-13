/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:05:45 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/12 17:33:50 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	lexer(t_data *data)
{
	if(!check_open_quotes(data->prompt))
		return (perror("Error: not all quotes were closed"), 1);
	data->tokens = tokenizer(data);
	processing(data);
	expander(data->tokens, data);
	remove_empty_tokens(data);
	if (data->n_tokens == 0)
		ft_exit_err(NULL, data);
	// test_tokens(data->tokens);
	return 0;
}

bool	check_open_quotes(char *prompt)
{
	bool	in_single;
	bool	in_double;
	int	i;

	in_double = false;
	in_single = false;
	i = 0;
	while(prompt[i])
	{
		if(prompt[i] == '\"' && !in_single)
			in_double = !in_double;
		else if(prompt[i] == '\'' && !in_double)
			in_single = !in_single;
		i++;
	}
	return (!in_double && !in_single);
}

void	processing(t_data *data)
{
	//test_tokens(data->tokens);
	update_type(data);
	update_index(data->tokens, data);
	check_types(data);
	// test_tokens(data->tokens);
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
	int	i;

	tokens = data->tokens;
	i = 0;
	while (tokens != NULL)
	{
		i = 0;
		while (tokens->value[i] != '\0')
		{
			if(tokens->value[i] == PIPE_PROMPT)
			{
				tokens->type = check_pipe(tokens, data);
				break ;
			}
			if (tokens->value[i] == '<' || tokens->value[i] == '>')
			{
				tokens->type = check_redirect(tokens, data);
				break;
			}
			i++;
		}
		tokens = tokens->next;
	}

}

t_type	check_pipe(t_token *tokens, t_data *data) //should be this token specific
{
	int	i;
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
	return(STRING);
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
	return(new);
}
