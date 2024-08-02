/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:05:45 by fjoestin          #+#    #+#             */
/*   Updated: 2024/08/02 16:04:17 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(t_data *data)
{
	t_token *tokens;
	
	if(!check_open_quotes(data->prompt))
		return (perror("Error: not all quotes were closed"), 1);
	tokens = tokenizer(data);
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
