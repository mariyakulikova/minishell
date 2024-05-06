/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:30 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/06 13:40:44 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_only_space(char *promt)
{
	while (*promt)
	{
		if (!is_space(*promt))
			return (0);
		promt++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	data = NULL;
	data_init(&data, envp);
	while (1)
	{
		data->prompt = readline(ENTRY_PROMPT);
		add_history(data->prompt);
		if (is_only_space(data->prompt) || ft_strlen(data->prompt) == 0)
			continue ;
		if (lexer(data))
			continue ;
		if (parser(data))
			continue ;
		if (executer(data))
			continue ;
	}
	return (0);
}
