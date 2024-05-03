/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:13:59 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/06 11:44:59 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read(int fd, char *buf, char *stash)
{
	ssize_t	r;
	char	*temp;

	r = 1;
	while (r > 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			free(stash);
			return (NULL);
		}
		if (r == 0)
			return (stash);
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

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*stash;

	if (BUFFER_SIZE <= 0 || fd == -1 || read(fd, NULL, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (!stash)
		stash = ft_strdup("");
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	stash = ft_read(fd, buf, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(&stash);
	free(buf);
	return (line);
}
