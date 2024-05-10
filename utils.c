/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:22:33 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/10 17:07:22 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_msg(char *s1, char *s2)
{
	write(2, s1, ft_strlen(s1));
	write(2, ": ", 2);
	write(2, s2, ft_strlen(s2));
	write(2, "\n", 1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (*(split + i))
	{
		free(*(split + i));
		i++;
	}
	free(split);
}

void	my_exit(t_param *params, char *err, char *name)
{
	char	*strerr;

	strerr = strerror(errno);
	write(2, "pipex: ", 8);
	if (ft_strcmp(err, ERR_CMD) == 0)
		err_msg(err, name);
	else if (ft_strcmp(err, ERR_OPEN) == 0)
		err_msg(strerr, name);
	else
		perror(err);
	free_param(params);
	exit(EXIT_FAILURE);
}

void	open_files(char *infile, char *outfile, t_param *params)
{
	if (params->here_doc)
	{
		params->infile_fd = here_doc(params);
		params->outfile_fd = open(outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (params->outfile_fd == -1)
			my_exit(params, ERR_OPEN, outfile);
	}
	else
	{
		params->infile_fd = open(infile, O_RDONLY);
		if (params->infile_fd == -1)
			my_exit(params, ERR_OPEN, infile);
		params->outfile_fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (params->outfile_fd == -1)
			my_exit(params, ERR_OPEN, outfile);
	}
}

void	close_files(t_param *param)
{
	close(param->infile_fd);
	close(param->outfile_fd);
	if (param->here_doc)
		unlink(TMP_FILE);
}

int	split_size(char **split)
{
	int	size;

	size = 0;
	while(*split)
	{
		size++;
		split++;
	}
	return (size);
}
