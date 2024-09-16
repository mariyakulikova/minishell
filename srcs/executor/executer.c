/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:26 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/16 10:27:32 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	exe_in_parent(t_exe_data *exe_data, t_data *data, int idx)
{
	if (set_fd(exe_data->fd_tab, data, 0))
	{
		data->exit_status = 1;
		return (1);
	}
	if (dup_fd(exe_data->fd_tab, 0, 2))
	{
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = data->builtin_tab[idx](data, data->cmd_tab[0]);
	if (reset_std(data, exe_data->fd_tab))
		return (1);
	return (0);
}

static void	child_process(t_exe_data *exe_data, t_data *data, int i)
{
	if (set_fd(exe_data->fd_tab, data, i))
		exit(1);
	link_pipes(exe_data->pipe_tab, exe_data->pids_size, i);
	if (dup_fd(exe_data->fd_tab, (i * 2), 2))
		exit(1);
	close_fd(exe_data->pipe_tab, exe_data->pipes_size);
	close_fd(exe_data->fd_tab, exe_data->pids_size * 2);
	execute_cmd(data, i);
}

static int	proceed_cmd(t_exe_data *exe_data, t_data *data)
{
	int	i;
	int	idx;

	i = -1;
	idx = get_builtin_idx(data, **(data->cmd_tab));
	if (data->cmd_size == 1 && idx > -1)
		return (exe_in_parent(exe_data, data, idx));
	while (++i < data->cmd_size)
	{
		*(exe_data->pid_tab + i) = fork();
		if (*(exe_data->pid_tab + i) == -1)
		{
			perror("fork");
			return (1);
		}
		if (*(exe_data->pid_tab + i) == 0)
			child_process(exe_data, data, i);
	}
	return (0);
}

int	executer(t_data *data)
{
	t_exe_data	*exe_data;
	int			code;

	exe_data = NULL;
	code = 0;
	if (init_exe_data(&exe_data, data))
		return (free_exe_data(exe_data, 1));
	execute_heredoc(data, exe_data);
	if (*data->cmd_tab)
		code = proceed_cmd(exe_data, data);
	close_fd(exe_data->fd_tab, exe_data->pids_size * 2);
	close_fd(exe_data->pipe_tab, exe_data->pipes_size);
	waitpids(exe_data, data);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	unlink_fd_list_tab(data);
	return (free_exe_data(exe_data, code));
}
