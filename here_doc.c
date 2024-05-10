/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:14:41 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/10 16:26:58 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_read(int fd, char *buf, char *stash)
{
	ssize_t	r;
	char	*temp;

	while (1)
	{
		r = read(fd, buf, BUFF_SIZE);
		if (r == -1)
		{
			free(stash);
			return (NULL);
		}
		*(buf + r) = '\0';
		temp = stash;
		stash = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(stash, ENDL))
			break ;
	}
	return (stash);
}

static char	*ft_get_line(char **stash)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	while (*(*stash + i) && *(*stash + i) != ENDL)
		i++;
	temp = *stash;
	line = ft_substr(temp, 0, i + 1);
	*stash = ft_substr(temp, i + 1, ft_strlen(temp) - 1);
	free(temp);
	if (!line)
	{
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

static int	pgnl(char *line)
{
	char		*buf;
	static char	*stash;

	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (-1);
	}
	buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buf)
		return (-1);
	stash = ft_read(0, buf, stash);
	if (!stash)
		return (-1);
	line = ft_get_line(&stash);
	free(buf);
	return (0);
}

int	here_doc(t_param *param)
{
	int		fd;
	char	*line;

	fd = open(TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		my_exit(param, ERR_OPEN, TMP_FILE);
	while (1)
	{
		write(1, "> ", 3);
		line = get_next_line(0);
		if (!ft_strcmp(line, param->limiter))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	fd = open(TMP_FILE, O_RDONLY);
	if (fd == -1)
		my_exit(param, ERR_OPEN, TMP_FILE);
	free(line);
	return (fd);
}
