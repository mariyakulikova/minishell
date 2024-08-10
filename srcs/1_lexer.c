/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:05:45 by fjoestin          #+#    #+#             */
/*   Updated: 2024/08/08 14:42:54 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(t_data *data)
{
	
	if(!check_open_quotes(data->prompt))
		return (perror("Error: not all quotes were closed"), 1);
	data->tokens = tokenizer(data);
	processing(data);
	/* expender(&tokens); */
	test_tokens(data->tokens);
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
	update_index(data->tokens, data);
	update_type(data);
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
			real_pipe(tokens, data);
		i++;
	}
	return(STRING);
}

void	real_pipe(t_token *token, t_data *data)
{
	char	*prompt;
	char	**split;
	int		wpipe;
	int		size;
	int		j = 1;
	t_token	*tmp;// will i have to initialize?

	prompt = token->value;
	wpipe = str_chr_idx(prompt, PIPE_PROMPT);
	if (prompt[wpipe] != 0 && prompt[wpipe + 1] != '\0')
	{
		split = (char **)malloc(sizeof(char *) * 4);
		size = 3;
	}
	else
	{
		split = (char **)malloc(sizeof(char *) * 3);
		size = 2;
	}
	if (wpipe == 0)
	{
		split[0] = ft_strdup("|");
		split[1] = ft_substr(prompt, 1, (ft_strlen(prompt) - 1));
	}
	else
	{
		split[0] = ft_substr(prompt, 0, wpipe);
		split[1] = ft_strdup("|");
		if (prompt[wpipe + 1])
		{
			split[2] = ft_substr(prompt, (wpipe + 1), (ft_strlen(prompt) - wpipe)); 
		}
	}
	split[size] = NULL;
	token->value = ft_strdup(split[0]);
	while (split[j] && token != NULL)
	{
		tmp = ft_new_token(split[j]);
		tmp->prev = token;
		if (token->next)
		{
			tmp->next = token->next;
			token->next->prev = tmp;
		}
		else
			tmp->next = NULL;
		token->next = tmp;
		if (token->next)
			token = token->next;
		j++;
	}
	processing(data);
}
t_token	*ft_new_token(char *line)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->value = ft_strdup(line);
	new->index = INT_MAX; 
	new->join = TRUE;
	new->quotes = get_if_quotes(new->value);
	new->type = OPERAND;
	new->prev = NULL;
	new->next = NULL;
	return(new);
}