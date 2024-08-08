/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:05:45 by fjoestin          #+#    #+#             */
/*   Updated: 2024/08/07 18:35:26 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(t_data *data)
{
	t_token *tokens;
	
	if(!check_open_quotes(data->prompt))
		return (perror("Error: not all quotes were closed"), 1);
	tokens = tokenizer(data);
/* 	processing(&tokens);
	expender(&tokens); */
	test_tokens(tokens);
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

void	processing(t_token **tokens)
{
	update_index(&tokens);
	update_type(&tokens);
}

void	update_index(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		tokens->index = i;
		i++;
		tokens = tokens->next;
	}
}

void	update_type(t_token *tokens)//**
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		while (tokens->value[i] != '\0')
		{
			if(tokens->value[i] == PIPE_PROMPT)
				tokens->type = check_pipe(&tokens);
			i++;
		}
		
		tokens = tokens->next;
	}
	
}

t_type	check_pipe(t_token *tokens) //should be this token specific
{
	int	i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	if (tokens->value[0] == PIPE_PROMPT && tokens->value[1] == '\0')
		return (PIPE);

	while (tokens->value[i])
	{
		if (tokens->value[i] == SINGLE_QUOTE || tokens->value[i] == DOUBLE_QUOTE)
		{
			in_quotes = !in_quotes;
		}
		if (tokens->value[i] == PIPE_PROMPT && !in_quotes)
		{
			real_pipe
		}
		
		i++;

	}
	
}

void	real_pipe(t_token *token)
{
	char	*prompt;
	char	**split;
	int		wpipe;
	int		i;
	int		size;
	int		j = 0;

	prompt = token->value;
	wpipe = str_chr_idx(prompt, PIPE_PROMPT);
	i = 0;
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
		split[0] = ft_strdup(PIPE_PROMPT);
		split[1] = ft_substr(prompt, 1, (ft_strlen(prompt) - 1));
	}
	else
	{
		split[0] = ft_substr(prompt, 0, (wpipe - 1));
		split[1] = ft_strdup(PIPE_PROMPT);
		if (prompt[wpipe + 1])
		{
			while (prompt[wpipe + i])
				i++;
			split[2] = ft_substr(prompt, ++wpipe, i); 
		}
	}
	split[size] = '\0';

	while (j < size)
	{
		ft_new_token(token, split[j]);
		j++;
	}
		
	//call processing
}
void	ft_new_token(t_token *token, char *line)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->value = ft_strdup(line);
	new->index = INT_MAX;
	new->
	new->quotes = get_if_quotes(new->value);

	new->prev = ;
	new->next = NULL;
	new->type = STRING;

}