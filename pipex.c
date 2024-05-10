/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:51:52 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/10 16:26:58 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waitpids(t_param *param, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(param->pids[i], NULL, 0);
		i++;
	}
}

void	close_pipes(t_param *param)
{
	int	i;

	i = 0;
	while (i < (param->pipes_size))
	{
		close(*(param->pipes + i));
		i++;
	}
}

static void	my_execve(t_param *param, char **cmd)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(param->cmds_path, cmd[0]);
	if (cmd_path == NULL)
		my_exit(param, ERR_CMD, cmd[0]);
	if (execve(cmd_path, cmd, param->envp) == -1)
		my_exit(param, ERR_EXEC, NULL);
}

static int	my_dup(int in, int out)
{
	int	fd1;
	int	fd2;

	fd1 = dup2(in, STDIN_FILENO);
	fd2 = dup2(out, STDOUT_FILENO);
	if (fd1 == -1 || fd2 == -1)
		return (-1);
	else
		return (0);
}

void	child(t_param *param, int i)
{
	param->pids[i] = fork();
	if (param->pids[i] == -1)
		my_exit(param, ERR_FORK, NULL);
	if (param->pids[i] == 0)
	{
		if (i == 0)
		{
			if (my_dup(param->infile_fd, param->pipes[1]) == -1)
				my_exit(param, ERR_DUP2, NULL);
		}
		else if (i == param->cmd_num - 1)
		{
			if (my_dup(param->pipes[2 * i - 2], param->outfile_fd) == -1)
				my_exit(param, ERR_DUP2, NULL);
		}
		else
		{
			if (my_dup(param->pipes[2 * i - 2], param->pipes[2 * i + 1]) == -1)
				my_exit(param, ERR_DUP2, NULL);
		}
		close_pipes(param);
		close_files(param);
		my_execve(param, param->cmds[i]);
	}
}
