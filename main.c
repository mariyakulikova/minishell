/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:30:50 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/21 15:28:20 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static int	is_argc_valid(t_param *param, int argc, char **argv)
{
	int	min_valid_amount;

	if (!ft_strcmp(argv[1], "here_doc"))
	{
		param->here_doc = 1;
		min_valid_amount = 6;
	}
	else
		min_valid_amount = 5;
	if (argc < min_valid_amount)
		return (-1);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_param	*param;
	int		i;

	data = NULL;
	if (argc != 1)
	{
		perror("Wrong number of arguments!");
		exit(EXIT_FAILURE);
	}
	param = param_init();
	init_data(&data, envp);
	// while (1)
	data->prompt = readline(PROMPT);
	set_param(param, 2, data->prompt, envp);
	i = 0;
	while (i < param->cmd_num)
		child(param, i++);
	close_pipes(param);
	close_files(param);
	waitpids(param, param->cmd_num);
	free_param(param);
	return (EXIT_SUCCESS);
}
