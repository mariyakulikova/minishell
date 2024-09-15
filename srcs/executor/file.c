/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:17:11 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/15 14:47:07 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	reset_std(t_data *data, int *fd)
{
	if (fd[0] > 2)
	{
		if (ft_dup2(data->orig_std_in, STDIN_FILENO) == -1)
			return (1);
		close(data->orig_std_in);
		data->orig_std_in = dup(STDIN_FILENO);
		if (data->orig_std_in == -1)
			return (1);
	}
	if (fd[1] > 2)
	{
		if (ft_dup2(data->orig_std_out, STDOUT_FILENO) == -1)
			return (1);
		close(data->orig_std_out);
		data->orig_std_out = dup(STDOUT_FILENO);
		if (data->orig_std_out == -1)
			return (1);
	}
	return (0);
}

static int	open_file(t_llist *list)
{
	int	fd;

	fd = -1;
	if (*(t_type *)list->key == RED_OUT)
		fd = open((char *)list->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (*(t_type *)list->key == APPEND)
		fd = open((char *)list->value, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (*(t_type *)list->key == RED_IN)
		fd = open((char *)list->value, O_RDWR, 0644);
	return (fd);
}

int	dup_fd(int *fd_tab, int j, int size)
{
	int	i;
	int	code;

	i = j - 1;
	code = 0;
	while (++i < j + size)
	{
		if (*(fd_tab + i) > 2)
		{
			if (i % 2 == 0)
				code = dup2(*(fd_tab + i), STDIN_FILENO);
			else
				code = dup2(*(fd_tab + i), STDOUT_FILENO);
			if (code == -1)
			{
				perror("dup2");
				return (code);
			}
		}
	}
	return (0);
}

int	set_fd(int *fd_tab, t_data *data, int i)
{
	t_llist	*fd_list;
	int		type;

	if (*(data->fd_list_tab + i) == NULL)
		return (0);
	fd_list = *(data->fd_list_tab + i);
	while (fd_list)
	{
		if (*(t_type *)fd_list->key != HERE_DOC)
		{
			type = get_stream_type(*(t_type *)fd_list->key);
			if (*(fd_tab + (i * 2) + type) > 2)
				close(*(fd_tab + (i * 2 + type)));
			*(fd_tab + (i * 2) + type) = open_file(fd_list);
			if (*(fd_tab + (i * 2) + type) == -1)
			{
				perror((char *)fd_list->value);
				return (1);
			}
		}
		fd_list = fd_list->next;
	}
	return (0);
}
