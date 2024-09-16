/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:00:34 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/16 18:34:57 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fd(int *fd, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (*(fd + i) > 2)
			close(*(fd + i));
	}
}

void	waitpids(t_exe_data *exe_data, t_data *data)
{
	int	i;

	i = 0;
	(void)data;
	while (i < exe_data->pids_size)
	{
		waitpid(*(exe_data->pid_tab + i), &data->exit_status, 0);
		i++;
	}
}

int	link_pipes(int *pipe_tab, int size, int i)
{
	if (size == 1)
		return (0);
	if (i == 0)
	{
		close(pipe_tab[0]);
		dup2(pipe_tab[1], STDOUT_FILENO);
		close(pipe_tab[1]);
	}
	else if (i == size - 1)
	{
		close(pipe_tab[2 * i - 1]);
		dup2(pipe_tab[2 * i - 2], STDIN_FILENO);
		close(pipe_tab[2 * i - 2]);
	}
	else
	{
		dup2(pipe_tab[2 * i + 1], STDOUT_FILENO);
		dup2(pipe_tab[2 * i - 2], STDIN_FILENO);
		close(pipe_tab[2 * i + 1]);
		close(pipe_tab[2 * i - 2]);
	}
	return (0);
}

int	unlink_fd_list_tab(t_data *data)
{
	int		i;
	t_llist	*curr;
	char	*fname;

	i = -1;
	while (++i < data->cmd_size)
	{
		curr = *(data->fd_list_tab + i);
		if (curr && *(t_type *)curr->key == HERE_DOC)
		{
			fname = get_fname("/var/tmp/.temp", i);
			if (unlink(fname) == -1)
			{
				perror("unlink");
				free(fname);
				return (1);
			}
			free(fname);
		}
	}
	return (0);
}
