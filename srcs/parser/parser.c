/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:38:20 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/16 21:47:27 by mkulikov         ###   ########.fr       */
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
		if (is_red(curr->value))
		{
			curr->type = RED;
			if (curr->next)
			{
				curr = curr->next;
				curr->type = RED;
			}
		}
		else
			curr = curr->next;
	}
}
// test
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

	mock_tokens(data->tokens); // delete after lexer will be done
	data->cmd_size = count_tokens(data->tokens, PIPE) + 1;
	data->fd_tab = (int *)malloc(sizeof(int) * data->cmd_size * 2);
	if (!data->fd_tab)
		return (1);
	ft_memset(data->fd_tab, -1, sizeof(int) * data->cmd_size * 2);
	if (parse_red(data))
		return (1);
	data->cmd_tab = (char ***)malloc(sizeof(char **) * data->cmd_size);
	if (!data->cmd_tab)
		return (1);
	i = -1;
	while (++i < data->cmd_size)
		data->cmd_tab[i] = NULL;
	if (parse_cmd(data))
		return (1);
	return (0);
}
