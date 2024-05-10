/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:09:25 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/10 17:30:38 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_param(t_param *param)
{
	int	i;

	i = 0;
	if (param->cmds != NULL)
	{
		while (*(param->cmds + i))
		{
			free_split(*(param->cmds + i));
			i++;
		}
		free(param->cmds);
	}
	if (param->cmds_path != NULL)
		free_split(param->cmds_path);
	if (param->pids != NULL)
		free(param->pids);
	if (param->pipes != NULL)
		free(param->pipes);
	if (param->limiter != NULL)
		free(param->limiter);
	free(param);
}

t_param	*param_init(void)
{
	t_param	*param;

	param = (t_param *)malloc(sizeof(t_param));
	if (!param)
		exit (EXIT_FAILURE);
	param->pids = NULL;
	param->pipes = NULL;
	param->path = NULL;
	param->cmds_path = NULL;
	param->cmds = NULL;
	param->envp = NULL;
	param->here_doc = 0;
	param->limiter = NULL;
	return (param);
}

static int	*pipes_init(t_param *param, int size)
{
	int	*pipes;
	int	i;

	pipes = (int *)malloc(sizeof(int) * size);
	if (!pipes)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		if (pipe(pipes + i) < 0)
			my_exit(param, ERR_PIPE, NULL);
		i += 2;
	}
	return (pipes);
}

void	set_param(t_param *param, int argc, char *prompt, char **envp)
{
	char	**splited_prompt;
	int		size;
	int		i;

	if (param->here_doc)
	{
		// param->limiter = ft_strjoin(argv[2], "\n");
		// if (!param->limiter)
		// 	exit(EXIT_FAILURE);
	}
	splited_prompt = ft_split(prompt, ' ');
	size = split_size(splited_prompt);
	param->cmd_num = size - 2;
	param->pipes_size = (size - 1) * 2;
	open_files(*(splited_prompt), *(splited_prompt + size - 1), param);
	param->pids = (pid_t *)malloc(sizeof(pid_t) * size);
	if (!param->pids)
		exit(EXIT_FAILURE);
	param->envp = envp;
	set_path_value(param, envp);
	param->cmds_path = ft_split(param->path, ':');

	parse_cmds(param, size - 1, splited_prompt);
	param->pipes = pipes_init(param, param->pipes_size);
}
