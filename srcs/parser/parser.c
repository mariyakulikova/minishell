/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:38:20 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/16 13:02:14 by mkulikov         ###   ########.fr       */
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

// static void	init_parser_data(t_data *data)
// {
// 	int	i;

// 	data->cmd_size = count_tokens(data->tokens, PIPE) + 1;
// 	data->cmd_tab = (char ***)malloc(sizeof(char **) * data->cmd_size);
// 	i = -1;
// 	while (++i < data->cmd_size)
// 		data->cmd_tab[i] = NULL;
// 	data->fd_tab = (int *)malloc(sizeof(int) * data->cmd_size * 2);
// 	ft_memset(data->fd_tab, -1, data->cmd_size);
// }

void	test(char ***arr, int size)
{
	int i = -1;
	int j;
	while (++i < size)
	{
        j = 0;
        while (arr[i][j] != NULL)
        {
            printf("%s ", arr[i][j]);
            j++;
        }
        printf("\n");
	}
}

int	parser(t_data *data)
{
	int	i;

	data->cmd_size = count_tokens(data->tokens, PIPE) + 1;
	data->fd_tab = (int *)malloc(sizeof(int) * data->cmd_size * 2);
	ft_memset(data->fd_tab, -2, data->cmd_size);
	if (parse_red(data))
		return (1);
	data->cmd_tab = (char ***)malloc(sizeof(char **) * data->cmd_size);
	i = -1;
	while (++i < data->cmd_size)
		data->cmd_tab[i] = NULL;
	if (parse_cmd(data))
		return (1);
	test(data->cmd_tab, data->cmd_size);
	return (0);
}

// if (curr->type == RED || curr->type == HERE_DOC)
// 				handle_red(data->fd_tab + (i * 2), curr);
