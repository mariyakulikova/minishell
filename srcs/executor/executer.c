/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:26 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/30 20:15:41 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// void fd_test(int *fd, int size, t_data *data, int i)
// {
// 	char *pid = ft_itoa(getpid());
// 	int len = ft_strlen(pid);
// 	write(2, pid, len);
// 	write(2, "\n", 1);
// 	write(2, "i - ", 5);
// 	write(2, ft_itoa(i), 1);
// 	write(2, "\n", 1);
// 	write(2, "cmd - ", 7);
// 	write(2, **(data->cmd_tab + i), ft_strlen(**(data->cmd_tab + i)));
// 	write(2, "\n", 1);
// 	for (int i = 0; i < size; i++)
// 	{
// 		char *c_fd = ft_itoa(fd[i]);
// 		int fd_len = ft_strlen(c_fd);
// 		write(2, c_fd, fd_len);
// 		write(2, " ", 1);
// 	}
// 	write(2, "\n", 1);
// }

static void	child_process(t_exe_data *exe_data, t_data *data, int i)
{

	if (set_fd(exe_data->fd_tab, data, (i * 2)))
		exit(1);
	if (set_fd(exe_data->fd_tab, data, (i * 2) + 1))
		exit(1);
	link_pipes(exe_data->pipe_tab, exe_data->fd_tab, exe_data->pids_size, i);
	if (dup_fd(exe_data->fd_tab, (i * 2), 2))
		exit(1);
	close_fd(exe_data->pipe_tab, exe_data->pipes_size);
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
	code = proceed_cmd(exe_data, data);
	close_fd(exe_data->pipe_tab, exe_data->pipes_size);
	close_fd(exe_data->fd_tab, exe_data->pids_size * 2);
	waitpids(exe_data, data);
	data->exit_status = code; // ??? need to check TODO
	return (free_exe_data(exe_data, code));
}
