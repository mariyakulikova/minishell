/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:08:48 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/06 23:46:13 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_new(char *prompt, int start, int end)
{
	t_token	*new;
	new = malloc(sizeof(t_token));
	new->value

	return (new);
}

int	lexer(t_data *data)
{
	char	*prompt;
	int		start;
	int		end;

	prompt = ft_strtrim(data->prompt, WHITE_SPACE);
	start = 0;
	end = 0;
	while (prompt[start])
	{
		if (prompt[start] == SINGLE_QUOTE)
			end = check_single_quote(prompt[start]);
		else if (prompt[start] == DOBLE_QUOTE)
			end = check_double_quote(prompt[start]);
		else if (ft_isprint(prompt[start]))
			end = check_word(prompt[start]);

		start++;
		if (end > 0)
		{
			token_new(prompt, start, end);
			start += end;
			end = 0;
		}
	}
	
	return 0;
	// curr = NULL;
	// if (is_prompt_valid(prompt))
	// 	return error;
	// while (*prompt)
	// {
	// 	if (!curr)
	// 		curr = tocken_new(&prompt);
	// 	else
	// 		curr->next = tocken_new(&prompt);
	// }
}

int	check_single_quote(char *prompt)
{
	char *tmp;
	int		i;

	tmp = prompt;
	i = 0;
	while(tmp[i])
	{
		if(tmp[i] == SINGLE_QUOTE)
			return (i) ;
		i++;
	}
	return (-1);
}

int	check_double_quote(char *prompt)
{
	
}

int check_word(char *prompt)
{
	
}