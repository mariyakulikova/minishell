/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:30 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/03 17:50:43 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	data = NULL;
	data_init(&data, envp);

	char *line = readline("Enter a line: ");
	data->promt = "echo";
	ft_echo(data);
	return (0);
}
