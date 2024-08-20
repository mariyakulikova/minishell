/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:26 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/20 12:50:20 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	proceed_cmd(t_exe_data *exe_data, t_data *data)
{
	*(exe_data->pids) = fork();
	if (*(exe_data->pids) == -1)
		return (1);
	if (*(exe_data->pids) == 0)
	{
		update_fd_tab(data->fd_tab, 2);
		execute_cmd(data, 0);
		close_fd(data->fd_tab, 2);
	}
	return (0);
}

static int	proceed_multi_cmd(t_exe_data *exe_data, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_size)
	{
		*(exe_data->pids +  i) = fork();
		if (*(exe_data->pids + i) == -1)
			return (1);
		if (*(exe_data->pids) == 0)
		{
			execute_cmd(data, i);
			close_fd(data->fd_tab, data->cmd_size * 2);
			close_fd(exe_data->pipes, (data->cmd_size - 1) * 2);
		}
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
	if (data->cmd_size == 1)
		code = proceed_cmd(exe_data, data);
	else
		code = proceed_multi_cmd(exe_data, data);
	close_fd(exe_data->pipes, exe_data->pipes_size);
	close_fd(data->fd_tab, data->cmd_size * 2);
	if (data->has_heredoc)
		unlink(TEMP_FILE);
	waitpids(exe_data, data);
	// reset_std(data);
	return (free_exe_data(exe_data, code));
}
