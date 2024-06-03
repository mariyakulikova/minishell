/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:05:45 by fjoestin          #+#    #+#             */
/*   Updated: 2024/06/02 17:14:30 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexer(t_data *data)
{
	t_lexer_help *lexer;
	
	if(!check_open_quotes(data->prompt))
		return (perror("Error: not all quotes were closed"), 1);
	lexer = init_lh(data);
	

}

t_lexer_help	*init_lh(t_data *data)
{
	t_lexer_help	*lh;
	
	lh = (t_lexer_help *)malloc(sizeof(t_lexer_help));
	if (!lh)
		return (NULL);
	lh->line = ft_strdup(data->prompt);
	lh->result = NULL;
	lh->temp = NULL;
	lh->size = 0;
	lh->start = 0;
	lh->in_quotes = 0;
	lh->quotes_type = 0;
	lh->i = 0;
	lh->curr_t = 0;
	return (lh);
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
// 		if (data->line[i] == ' ' && (!in_d_quotes || !in_s_quotes))
// 		{
			
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
