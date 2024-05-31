/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:05:45 by fjoestin          #+#    #+#             */
/*   Updated: 2024/05/31 14:44:18 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(t_data *data)
{
	t_token *token;
	
	if(!check_open_quotes(data->prompt))
		return (perror("Error: not all quotes were closed"));
	
	

}

// void	tokenizer(t_token *token, t_data *data)
// {
// 	int	i;
// 	bool	in_s_quotes;
// 	bool	in_d_quotes;
	
// 	i = 0;
// 	in_d_quotes = false;
// 	in_s_quotes = false;
// 	data->line = ft_strtrim(data->prompt, WHITE_SPACE);
// 	while(data->line[i])
// 	{
// 		if (data->line[i] == ' ' )
// 		{
// 			/* code */
// 		}
		
// 		if(data->line[i] == '\"')
// 	}
// }

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
