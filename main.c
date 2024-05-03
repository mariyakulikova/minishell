/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:14:30 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/03 11:24:03 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;

	char *line = readline ("Enter a line: ");

	printf("%s\n", line);
	free(line);
	return (0);
}
