/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:26 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/23 22:25:32 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	child_process(t_exe_data *exe_data, t_data *data, int i)
{

	if (set_fd(exe_data->fd_tab, data->fd_list_tab, (i * 2)))
		exit(1);
	if (set_fd(exe_data->fd_tab, data->fd_list_tab, (i * 2) + 1))
		exit(1);
	update_fd_tab(exe_data->fd_tab, (i * 2), 2);
	if (dup_fd(exe_data->fd_tab, (i * 2), 2))
		exit(1);
	execute_cmd(data, i);
}

static int	proceed_cmd(t_exe_data *exe_data, t_data *data)
{
	int	i;

	i = -1;
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
	t_exe_data *exe_data;
	int			code;

	exe_data = NULL;
	code = 0;
	if (init_exe_data(&exe_data, data))
		return (free_exe_data(exe_data, 1));
	(void)data;
	code = proceed_cmd(exe_data, data);
	// close_fd(exe_data->pipe_tab, exe_data->pipes_size);
	// close_fd(exe_data->fd_tab, exe_data->pids_size * 2);
	waitpids(exe_data, data);
	data->exit_status = code; // ??? need to check TODO
	return (free_exe_data(exe_data, code));
}
