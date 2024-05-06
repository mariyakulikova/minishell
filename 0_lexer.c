/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:08:48 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/06 16:27:44 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tocken	*tocken_new(char **prompt)
{
	t_tocken	*new;

	return (new);
}

int	lexer(t_data *data)
{
	// printf("This is lexer!\n");
	// char		*prompt;
	// t_tocken	*curr;

	// prompt = data->prompt;
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
