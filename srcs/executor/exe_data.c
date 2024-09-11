/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:47:26 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/11 16:01:42 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_exe_data(t_exe_data *exe_data, int code)
{
	if (!exe_data)
		return (code);
	if (exe_data->pipe_tab)
		free(exe_data->pipe_tab);
	if (exe_data->pid_tab)
		free(exe_data->pid_tab);
	if (exe_data->fd_tab)
		free(exe_data->fd_tab);
	free(exe_data);
	return (0);
}

static int	set_pipes(t_exe_data *exe_data)
{
	int	i;

	i = -1;
	while (++i < exe_data->pids_size - 1)
	{
		if (pipe(exe_data->pipe_tab + (i * 2)) == -1)
		{
			perror("pipe");
			return (1);
		}
	}
	return (0);
}

static void	set_default_fd(int *fd_tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (i % 2 == 0)
			*(fd_tab + i) = STDIN_FILENO;
		else
			*(fd_tab + i) = STDOUT_FILENO;
	}
}

int	init_exe_data(t_exe_data **exe_data, t_data *data)
{
	*exe_data = (t_exe_data *)malloc(sizeof(t_exe_data));
	if (!*exe_data)
		return (1);
	ft_memset((*exe_data), 0, sizeof(t_exe_data));
	(*exe_data)->pids_size = data->cmd_size;
	(*exe_data)->pid_tab =(pid_t *)malloc(sizeof(pid_t) * (*exe_data)->pids_size);
	if (!(*exe_data)->pid_tab)
		return (1);
	ft_memset((*exe_data)->pid_tab, -1, sizeof(pid_t) * (*exe_data)->pids_size);
	(*exe_data)->fd_tab = (int *)malloc(sizeof(int) * (*exe_data)->pids_size * 2);
	if (!(*exe_data)->fd_tab)
		return (1);
	set_default_fd((*exe_data)->fd_tab, (*exe_data)->pids_size * 2);
	(*exe_data)->pipes_size = ((*exe_data)->pids_size - 1) * 2;
	if ((*exe_data)->pipes_size == 0)
		return (0);
	(*exe_data)->pipe_tab = (int *)malloc(sizeof(int) * (*exe_data)->pipes_size);
	if (!(*exe_data)->pipe_tab)
		return (1);
	if (set_pipes(*exe_data))
		return (1);
	return (0);
}
