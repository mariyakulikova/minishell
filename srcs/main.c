/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:30 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/18 12:04:15 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	data = malloc(sizeof(t_data));
	if (argc != 1 && argv[1])
	{
		perror("Doesn't accept arguments!");
		exit(EXIT_FAILURE);
	}
	data_init(&data, envp);
	ft_minishell(data);
	return (0);
}

void	ft_minishell(t_data *data)
{
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

}
