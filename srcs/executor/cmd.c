/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:17:38 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/13 16:51:43 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**get_path_tab(t_data *data)
{
	t_env_lst	*curr;
	char		**path_tab;

	curr = data->lst;
	path_tab = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, "PATH") == 0)
		{
			path_tab = ft_split(curr->value, ':');
			if (!path_tab)
				return (NULL);
			break ;
		}
		curr = curr->next;
	}
	return (path_tab);
}

static int	check_permission(char *path)
{
	if (access(path, F_OK))
	{
		write(2, path, ft_strlen(path));
		write(2, " : No such file or directory\n", 29);
		exit(127);
	}
	if (access(path, X_OK))
	{
		write(2, path, ft_strlen(path));
		write(2, " : Permission denied\n", 21);
		exit(126);
	}
	return (0);
}

static char	*get_cmd_path(t_data *data, int i)
{
	int		j;
	char	**path_tab;
	char	*cmd_path;
	char	*temp;

	if (ft_strchr(**(data->cmd_tab + i), '/'))
		check_permission(**(data->cmd_tab + i));
	if (access(**(data->cmd_tab + i), F_OK | X_OK) == 0)
		return (**(data->cmd_tab + i));
	j = -1;
	path_tab = get_path_tab(data);
	if (!path_tab)
		return (NULL);
	while (*(path_tab + (++j)))
	{
		temp = ft_strjoin(*(path_tab + j), "/");
		cmd_path = ft_strjoin(temp, **(data->cmd_tab + i));
		free(temp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	free_split(path_tab);
	return (NULL);
}

static void	check_directory(char *path)
{
	struct stat	path_stat;
	int	size;
	
	stat(path, &path_stat);
	size = ft_strlen(path);
	if (S_ISDIR(path_stat.st_mode))
	{
		write(2, path, ft_strlen(path));
		if (ft_strchr(path, '/'))
			exit(err_msg(": Is a directory\n", 126));
		else
			exit(err_msg(" : command not found\n", 127));
	}
}

void	execute_cmd(t_data *data, int i)
{
	int		idx;
	char	*cmd_path;

	idx = get_builtin_idx(data, **(data->cmd_tab + i));
	if (idx > -1)
		exit((*(data->builtin_tab + idx))(data, data->cmd_tab[i]));
	else
	{
		cmd_path = get_cmd_path(data, i);
		if (!cmd_path)
		{
			write(2, **(data->cmd_tab + i), ft_strlen(**(data->cmd_tab + i)));
			write(2, " : command not found\n", 21);
			exit(127);
		}
		check_directory(cmd_path);
		execve(cmd_path, *(data->cmd_tab + i), data->envp);
	}
}
