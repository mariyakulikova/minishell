/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:17:11 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/21 13:25:16 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_file(t_llist *list)
{
	int	fd;

	fd = -1;
	if ((t_type)list->key == RED_OUT)
		fd = open((char *)list->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if ((t_type)list->key == APPEND)
		fd = open((char *)list->value, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if ((t_type)list->key == RED_IN)
		fd = open((char *)list->value, O_RDWR, 0644);
	else if ((t_type)list->key == HERE_DOC)
		fd = handle_heredoc((char *)list->value);
	return (fd);
}

void	update_fd_tab(int *fd_tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (*(fd_tab + i) < 0)
		{
			if (i % 2 == 0)
				*(fd_tab + i) = 0;
			else
				*(fd_tab + i) = 1;
		}
	}
}

int	dup_fd(int *fd_tab, int size)
{
	int	i;
	int	code;

	i = -1;
	code = 0;
	while (++i < size)
	{
		if (i % 2 == 0)
			code = dup2(*(fd_tab + i), STDIN_FILENO);
		else
			code = dup2(*(fd_tab + i), STDOUT_FILENO);
	}
	if (code)
	{
		perror("dup2");
		return (code);
	}
	return (code);
}

int	set_fd(int *fd, t_llist *fd_list_tab)
{
	t_llist	*fd_list;

	fd_list = fd_list_tab;
	printf("%s\n", (char *)fd_list->value);
	if (fd_list)
	{
		if (*fd != -1)
			close(*fd);
		*fd = open_file(fd_list);
		if (*fd == -1)
		{
			perror("open");
			return (1);
		}
		fd_list = fd_list_tab->next;
	}
	return (0);
}
