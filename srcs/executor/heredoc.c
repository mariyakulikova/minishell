/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:03 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/02 21:50:50 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	limiter_cmp(char *line, char *limiter)
{
	char	*temp;
	int		res;

	temp = ft_strdup(line);
	*(temp + ft_strlen(line) - 1) = '\0';
	res = ft_strcmp(temp, limiter);
	free(temp);
	return (res == 0);
}

static char	*get_fname(char *str, int i)
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
		write(1, "> ", 3);
		line = get_next_line(0);
		if (limiter_cmp(line, limiter))
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
		free(line);
	}
}

int	handle_heredoc(t_llist *fd_list, t_data *data, int i)
{
	int		fd;

	char	*fname;

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
	fd_list->value = (void *)fname;
	return (fd);
}

int	unlink_fd_list_tab(t_data *data)
{
	int		i;
	t_llist	*curr;

	i = -1;
	while (++i < data->cmd_size * 2)
	{
		curr = *(data->fd_list_tab + i);
		if (unlink_temp(curr))
			return (1);
	}
	return (0);
}
