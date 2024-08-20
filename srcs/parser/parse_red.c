/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:22:27 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/20 12:08:29 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void test_fd_tab(t_data *data)
{
	for (int k = 0; k < data->cmd_size * 2; k++)
	{
		printf("%d ", *(data->fd_tab + k));
	}
	printf("\n");
}

static int	get_std_type(char *val)
{
	int	std_type;

	std_type = 0;
	if (ft_strcmp(val, ">") == 0 || ft_strcmp(val, ">>") == 0)
		std_type = 1;
	if (ft_strcmp(val, "<") == 0 || ft_strcmp(val, "<<") == 0)
		std_type = 0;
	return (std_type);
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
		else
			if (i % 2 == 0)
				dup2(*(fd_tab + i), 0);
			else
				dup2(*(fd_tab + i), 1);
	}
}

static int	open_file(char *red, char *fname)
{
	int	fd;

	fd = -1;
	if (ft_strcmp(red, ">") == 0)
		fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(red, ">>") == 0)
		fd = open(fname, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (ft_strcmp(red, "<") == 0)
		fd = open(fname, O_RDWR, 0644);
	else if (ft_strcmp(red, "<<") == 0)
		fd = handle_heredoc(fname);
	return (fd);
}

static int	update_fd(t_data *data, t_token *token, int *fd)
{
	int		new_fd;
	char	*fname;

	new_fd = *fd;
	if (new_fd != -1)
		close(new_fd);
	if (token->next)
	{
		token->next->type = RED;
		fname = token->next->value;
	}
	else
		return (-1);
	new_fd = open_file(token->value, fname);
	if (new_fd == -1)
	{
		perror("open");
		data->exit_status = 1;
		return (-1);
	}
	*fd = new_fd;
	return (new_fd);
}

int	parse_red(t_data *data)
{
	t_token	*curr;
	int		*fd_tab;
	int		i;
	int		std_type;

	curr = data->tokens;
	fd_tab = data->fd_tab;
	i = 0;
	while (curr && i < data->cmd_size)
	{
		if (curr->type == RED)
		{
			std_type = get_std_type(curr->value);
			if (update_fd(data, curr, fd_tab + (i * 2) + std_type) < 0)
				return (1);
			curr = curr->next;
		}
		else if (curr->type == PIPE)
			++i;
		curr = curr->next;
	}
	// update_fd_tab(data->fd_tab, data->cmd_size * 2);
	return (0);
}
