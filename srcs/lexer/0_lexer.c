/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:08:48 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/16 12:47:27 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*token_new(char *prompt, int start, int end)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		exit(EXIT_FAILURE);
	new->value = ft_substr(prompt, start, end);
	new->index = INT_MAX;
	new->quotes = get_if_quotes(new->value);
	new->join = FALSE;
	new->prev = NULL;
	new->next = NULL;
	new->type = STRING;
	return (new);
}

t_token	*tokenizer(t_data *data)
{
	t_token	*token_lst;
	t_token	*tmp;
	int		start;
	int		end;

	data->line = ft_strtrim(data->prompt, WHITE_SPACE);
	start = 0;
	end = 0;
	token_lst = NULL;
	while (data->line[start])
	{
		if (end > 0)
		{
			tmp = token_new(data->line, start, end);
			ft_lstadd_back_ms(&token_lst, tmp);
			start += end + 1;
			end = 0;
			if (start >= (int)ft_strlen(data->line))
				break ;
		}
		end = check_prompt(data->line, &start);
		if (end == 0)
			start++;
	}
	return (token_lst);
}

int	check_prompt(char *prompt, int *start)
{
	int	end;

	end = 0;
	if (prompt[*start] == SINGLE_QUOTE)
		end = check_single_quote(&prompt[*start]);
	else if (prompt[*start] == DOUBLE_QUOTE)
		end = check_double_quote(&prompt[*start]);
	else if (ft_isprint(prompt[*start]))
		end = check_word(&prompt[*start]);
	return (end);
}

int	check_single_quote(char *prompt)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = prompt;
	i = 1;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == SINGLE_QUOTE && ft_isprint(tmp[i + 1]) == FALSE)
			return (++i);
		while (tmp[i] == SINGLE_QUOTE && ft_isprint(tmp[i + 1]) == TRUE)
		{
			if (tmp[i + j] == '\0' || is_space(tmp[i + j]) == TRUE)
				return (i + j);
			j++;
		}
		i++;
	}
	return (i);
}

int	check_double_quote(char *prompt)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = prompt;
	i = 1;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == DOUBLE_QUOTE && ft_isprint(tmp[i + 1]) == FALSE)
			return (++i);
		while (tmp[i] == DOUBLE_QUOTE && ft_isprint(tmp[i + 1]) == TRUE)
		{
			if (tmp[i + j] == '\0' || is_space(tmp[i + j]) == TRUE)
				return (i + j);
			j++;
		}
		i++;
	}
	return (i);
}
