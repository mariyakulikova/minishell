/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:03 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/16 18:32:13 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	limiter_cmp(char *line, char *limiter)
{
	char	*temp;
	int		res;

	if (ft_strlen(line) != ft_strlen(limiter))
		return (false);
	temp = ft_strdup(line);
	res = ft_strcmp(temp, limiter);
	free(temp);
	return (res == 0);
}

char	*get_fname(char *str, int i)
{
	char	*fname;
	char	*idx;

	idx = ft_itoa(i);
	fname = ft_strjoin(str, idx);
	free(idx);
	return (fname);
}

static void	read_heardoc(int fd, char *limiter, t_data *data)
{
	char	*line;
	int		i;

	while (1)
	{
		line = readline("> ");
		if (!line || limiter_cmp(line, limiter))
		{
			free(line);
			break ;
		}
		i = -1;
		while (*(line + (++i)))
		{
			if (*(line + i) == '$')
				line = expand_dollar(line, &i, data);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	handle_heredoc(t_llist *fd_list, t_data *data, int i)
{
	char	*fname;
	int		fd;

	fname = get_fname("/var/tmp/.temp", i);
	if (!fname)
		return (1);
	fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	read_heardoc(fd, (char *)fd_list->value, data);
	close(fd);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (-1);
	free(fname);
	return (fd);
}

int	execute_heredoc(t_data *data, t_exe_data *exe_data)
{
	int		i;
	t_llist	*fd_list;
	int		*fd;

	i = -1;
	while (++i < data->cmd_size)
	{
		fd_list = *(data->fd_list_tab + i);
		while (fd_list)
		{
			if (*(t_type *)fd_list->key != HERE_DOC)
			{
				fd_list = fd_list->next;
				continue ;
			}
			fd = exe_data->fd_tab + (i * 2);
			if (*fd > 2)
				close(*fd);
			*fd = handle_heredoc(fd_list, data, i);
			if (*fd == -1)
				return (1);
			fd_list = fd_list->next;
		}
	}
	return (0);
}
