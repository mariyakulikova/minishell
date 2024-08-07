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

/* void	processing(t_token **tokens)
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

void	update_type(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		while (tokens->value[i] != '\0')
		{
			if(tokens->value[i] == PIPE_PROMPT)
				check_pipe(&tokens);
			i++;
		}
		
		tokens = tokens->next;
	}
	
}

void	check_pipe(t_token *tokens) //should be this token specific
{
	int	i;

	i = 0;
	
	if(tokens->value[0] != PIPE_PROMPT)

	while (tokens->value[i])
	{
		

	}
	
} */