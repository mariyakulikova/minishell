/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:17:11 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/30 20:15:22 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			if (i % 2 == 0 )
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

	if (*(data->fd_list_tab + i) == NULL)
		return (0);
	fd_list = *(data->fd_list_tab + i);
	while (fd_list)
	{
		if (*(fd_tab + i) > 2)
			close(*(fd_tab + i));
		if (*(t_type *)fd_list->key == HERE_DOC)
			*(fd_tab + i) = handle_heredoc(fd_list, data, i);
		else
			*(fd_tab + i) = open_file(fd_list);
		if (*(fd_tab + i) == -1)
		{
			perror("open");
			return (1);
		}
		fd_list = fd_list->next;
	}
	return (0);
}
