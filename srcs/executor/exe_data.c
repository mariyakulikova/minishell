/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:47:26 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/19 13:08:36 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_exe_data(t_exe_data *exe_data, int code)
{
	if (!exe_data)
		return (code);
	if (exe_data->pipes)
		free(exe_data->pipes);
	if (exe_data->pids)
		free(exe_data->pids);
	//TODO free split;
	free(exe_data);
	return (code);
}

static int	set_pipes(t_exe_data *exe_data)
{
	int	i;

	i = -1;
	while (++i < (exe_data)->pipes_size)
	{
		if (pipe((exe_data)->pipes + (i * 2)) == -1)
		{
			perror("pipe");
			return (1);
		}
	}
	return (0);
}

static int	set_path_tab(t_exe_data *exe_data, t_data *data)
{
	int	i;

	i = -1;
	exe_data->path_tab = NULL;
	while (*(data->envp + (++i)))
	{
		if (ft_strncmp(*(data->envp + i), "PATH=", 5) == 0)
		{
			exe_data->path_tab = ft_split(*(data->envp + i), ':');
			if (!exe_data->path_tab)
				return (1);
			break ;
		}
	}
	return (0);
}

int	init_exe_data(t_exe_data **exe_data, t_data *data)
{
	*exe_data = (t_exe_data *)malloc(sizeof(t_exe_data));
	if (!*exe_data)
		return (1);
	(*exe_data)->pids_size = data->cmd_size;
	(*exe_data)->pids =(int *)malloc(sizeof(int) * (*exe_data)->pids_size);
	if (!(*exe_data)->pids)
		return (1);
	ft_memset((*exe_data)->pids, -1, sizeof(int) * (*exe_data)->pids_size);
	if (set_path_tab(*exe_data, data))
		return (1);
	(*exe_data)->pipes_size = ((*exe_data)->pids_size - 1) * 2;
	if ((*exe_data)->pipes_size == 0)
		return (0);
	(*exe_data)->pipes = (int *)malloc(sizeof(int) * (*exe_data)->pipes_size);
	if (!(*exe_data)->pipes)
		return (1);
	if (set_pipes(*exe_data))
		return (1);
	return (0);
}
