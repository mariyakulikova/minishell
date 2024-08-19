/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:26 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/18 15:04:41 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	free_exe_data(t_exe_data *exe_data, int code)
{
	if (!exe_data)
		return (code);
	if (exe_data->pipes)
		free(exe_data->pipes);
	if (exe_data->pids)
		free(exe_data->pids);
	free(exe_data);
	return (code);
}

static int	init_exe_data(t_exe_data **exe_data, t_data *data)
{
	int	i;

	*exe_data = (t_exe_data *)malloc(sizeof(t_exe_data));
	if (!*exe_data)
		return (1);
	(*exe_data)->pids_size = data->cmd_size;
	(*exe_data)->pids =(int *)malloc(sizeof(int) * (*exe_data)->pids_size);
	if (!(*exe_data)->pids)
		return (1);
	(*exe_data)->pipes_size = ((*exe_data)->pids_size - 1) * 2;
	if ((*exe_data)->pipes_size == 0)
		return (0);
	(*exe_data)->pipes = (int *)malloc(sizeof(int) * (*exe_data)->pipes_size);
	if (!(*exe_data)->pipes)
		return (1);
	i = -1;
	while (++i < (*exe_data)->pipes_size)
	{
		if (pipe((*exe_data)->pipes + (i * 2)) == -1)
		{
			perror("pipe");
			return (free_exe_data(*exe_data, 1));
		}
	}
	return (0);
}

int	executer(t_data *data)
{
	t_exe_data *exe_data;

	exe_data = NULL;
	if (init_exe_data(&exe_data, data))
		return (free_exe_data(exe_data, 1));
	(void)data;
	
	return (free_exe_data(exe_data, 0));
}
