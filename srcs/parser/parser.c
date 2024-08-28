/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:38:20 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/23 16:40:37 by mkulikov         ###   ########.fr       */
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
			if (add_fd_list(data->fd_list_tab + (i * 2), &curr))
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

// static void test(t_data *data)
// {
// 	t_llist *fd_list;
// 	char **cmd;
// 	int i = -1;
// 	while (++i < data->cmd_size)
// 	{
// 		cmd = *(data->cmd_tab + i);
// 		printf("cmd:\n");
// 		int j = 0;
// 		while (*(cmd + j))
// 		{
// 			printf("%s ", *(cmd + j));
// 			j++;
// 		}
// 		printf("\nfd_in:\n");
// 		fd_list = *(data->fd_list_tab + (i * 2));
// 		if (!fd_list)
// 			printf("NO!\n");
// 		else
// 		{
// 			while (fd_list)
// 			{
// 				printf("%s ", (char *)fd_list->value);
// 				fd_list = fd_list->next;
// 			}
// 			printf("\n");
// 		}
// 		printf("fd_out:\n");
// 		fd_list = *(data->fd_list_tab + (i * 2) + 1);
// 		if (!fd_list)
// 			printf("NO!\n");
// 		else
// 		{
// 			while (fd_list)
// 			{
// 				printf("%s ", (char *)fd_list->value);
// 				fd_list = fd_list->next;
// 			}
// 			printf("\n");
// 		}
// 	}
// }

int	parser(t_data *data)
{
	data->cmd_size = count_tokens(data->tokens, PIPE) + 1;
	data->fd_list_tab = (t_llist **)malloc(sizeof(t_llist *) * data->cmd_size * 2);
	if (!data->fd_list_tab)
		return (1);
	ft_memset(data->fd_list_tab, 0, sizeof(t_llist *) * data->cmd_size * 2);
	data->cmd_tab = (char ***)malloc(sizeof(char **) * data->cmd_size);
	if (!data->cmd_tab)
		return (1);
	ft_memset(data->cmd_tab, 0, sizeof(char **) * data->cmd_size);
	if (parse_tokens(data))
		return (1);
	// test(data);
	return (0);
}
