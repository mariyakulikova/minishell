/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:38:20 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/16 11:59:35 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_tokens(t_token *token, t_type type)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = token;
	while (curr)
	{
		if (curr->type == type)
			count++;
		curr = curr->next;
	}
	return (count);
}

static int	parse_tokens(t_data *data)
{
	t_token	*curr;
	int		i;

	curr = data->tokens;
	i = 0;
	while (curr && i < data->cmd_size)
	{
		if (is_red(curr))
		{
			if (add_fd_list(data->fd_list_tab + (i), &curr))
				return (222);
		}
		else if (curr->type == STRING)
		{
			*(data->cmd_tab + i) = update_cmd(*(data->cmd_tab + i), curr);
			if (!*(data->cmd_tab + i))
				return (111);
		}
		else if (curr->type == PIPE)
			++i;
		curr = curr->next;
	}
	return (0);
}

int	parser(t_data *data)
{
	data->cmd_size = count_tokens(data->tokens, PIPE) + 1;
	data->fd_list_tab = (t_llist **)malloc(sizeof(t_llist *) * data->cmd_size);
	if (!data->fd_list_tab)
		return (1);
	ft_memset(data->fd_list_tab, 0, sizeof(t_llist *) * data->cmd_size);
	data->cmd_tab = (char ***)malloc(sizeof(char **) * data->cmd_size);
	if (!data->cmd_tab)
		return (1);
	ft_memset(data->cmd_tab, 0, sizeof(char **) * data->cmd_size);
	if (parse_tokens(data))
		return (1);
	return (0);
}
