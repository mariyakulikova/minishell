/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:30 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/06 13:06:46 by mkulikov         ###   ########.fr       */
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
		data->promt = readline(TITLE);
		add_history(data->promt);
		if (!is_only_space(data->promt))
		{
			lexer(data);
			parser(data);
			executer(data);
		}
	}
	return (0);
}
