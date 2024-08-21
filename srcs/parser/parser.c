/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:38:20 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/21 10:54:36 by mkulikov         ###   ########.fr       */
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

//test
bool is_red(char *val)
{
	return (ft_strcmp(val, ">>") == 0 || ft_strcmp(val, ">") == 0 || ft_strcmp(val, "<<") == 0 || ft_strcmp(val, "<") == 0);
}
//test
void	mock_tokens(t_token *tokens)
{
	t_token *curr;

	curr = tokens;
	while (curr)
	{
		if (ft_strcmp(curr->value, ">") == 0)
		{
			curr->type = RED_OUT;
			if (curr->next)
			{
				curr = curr->next;
				curr->type = RED_OUT;
			}
		}
		else
			curr = curr->next;
	}
}

int	parser(t_data *data)
{
	mock_tokens(data->tokens); // delete after lexer will be done
	data->cmd_size = count_tokens(data->tokens, PIPE) + 1;
	data->fd_list_tab = (t_llist **)malloc(sizeof(t_llist *) * data->cmd_size);
	if (!data->fd_list_tab)
		return (1);
	ft_memset(data->fd_list_tab, 0, sizeof(t_llist *) * data->cmd_size);
	if (parse_red(data))
		return (1);
	data->cmd_tab = (char ***)malloc(sizeof(char **) * data->cmd_size);
	if (!data->cmd_tab)
		return (1);
	ft_memset(data->cmd_tab, 0, sizeof(char **) * data->cmd_size);
	if (parse_cmd(data))
		return (1);
	return (0);
}
