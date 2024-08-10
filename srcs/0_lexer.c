/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:08:48 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/07 18:18:22 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_new(char *prompt, int start, int end)
{
	t_token	*new;
	
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		exit(EXIT_FAILURE);
	new->value = ft_substr(prompt, start, end);
	new->index = INT_MAX;
	new->quotes = get_if_quotes(new->value);
	new->join = 1;
	new->prev = NULL;
	new->next = NULL;
	new->type = STRING;
	return (new);
}

t_token	*tokenizer(t_data *data)
{
	t_token *token_lst;
	t_token *tmp;
	char	*prompt;
	int		start;
	int		end;

	token_lst = NULL;
	tmp = NULL;
	prompt = ft_strtrim(data->prompt, WHITE_SPACE);
	start = 0;
	end = 0;
	while (prompt[start])
	{
		if (end > 0)
		{
			tmp = token_new(prompt, start, end);
			ft_lstadd_back_ms(&token_lst, tmp);
			start += end + 1;
			end = 0;
			if(start >= (int)ft_strlen(prompt))
				break;
		}
/* 		else if (end < 0)
			exit_err(ARG);  *///figure that out
		if (prompt[start] == SINGLE_QUOTE)
			end += check_single_quote(&prompt[start]);
		else if (prompt[start] == DOUBLE_QUOTE)
			end += check_double_quote(&prompt[start]);
		else if (ft_isprint(prompt[start]))
			end += check_word(&prompt[start]);
		else
			start++;
	}
	return (token_lst);
}

int	check_single_quote(char *prompt)
{
	char *tmp;
	int		i;

	tmp = prompt;
	i = 1;
	while(tmp[i])
	{
		if(tmp[i] == SINGLE_QUOTE)
			return (++i) ;
		i++;
	}
	return (i);
}

int	check_double_quote(char *prompt)
{
	char *tmp;
	int		i;
	int		j;

	tmp = prompt;
	i = 1;
	j = 0;
	while(tmp[i])
	{
		if(tmp[i] == DOUBLE_QUOTE && ft_isprint(tmp[i + 1]) == FALSE) 
			return (++i) ;
		while(tmp[i] == DOUBLE_QUOTE && ft_isprint(tmp[i + 1]) == TRUE)
		{
			if(tmp[i + j] == '\0' || is_space(tmp[i + j]) == TRUE)
				return(i + j);
			j++;
		}
		i++;
	}
	return (i);
}

int	check_word(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if(is_space(prompt[i + 1]))
			return(++i);
		i++;
	}
	return (i);
}