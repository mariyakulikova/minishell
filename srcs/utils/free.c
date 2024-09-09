/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:45:13 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/09 16:58:23 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

static void	free_env_lst(t_env_lst *list);

void	ft_free_data(t_data *data)
{
	free_env_lst(data->lst);
	free_env_lst(data->export_list);
	free_triple_tab(data->cmd_tab, data->cmd_size);
	free_tokens(data->tokens);
	free_llist(data->fd_list_tab, data->cmd_size * 2);
	//free built in func?how?
	//free_tab(data->builtin_name);
	//free_tab(data->envp);
	free(data->prompt);
	free(data->line);
	free(data->oldpwd);
}

void	free_triple_tab(char ***cmd_tab, int cmd_size)
{
	int	i;
	int	j;

	if (!cmd_tab)
		return ;
	i = 0;
	while (i < cmd_size)
	{
		j = 0;
		while (cmd_tab[i][j] != NULL)
		{
			free(cmd_tab[i][j]);
			j++;
		}
		free(cmd_tab[i]);
		i++;
	}
	free(cmd_tab);
}

void	free_tab(char **tab)
{
	int	i;
	int	stop;

	i = 0;
	if (!tab)
		return ;
	stop = get_size_tab(tab);
	while (i < stop)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	free_env_lst(t_env_lst *list)
{
	t_env_lst	*next;

	if(!list)
		return ;
	while (list != NULL)
	{
		next = list->next;
		free(list->key);
		if (list->value)
			free(list->value);
		free(list);
		list = next;
	}
}

void	free_tokens(t_token *tokens)
{
	if (!tokens)
		return ;
	while (tokens->next != NULL)
	{
		tokens = tokens->next;
		free(tokens->prev->value);
		free(tokens->prev);
	}
	free(tokens->value);
	free(tokens->next);
	free(tokens);
}

void	free_llist(t_llist **fd_list_tab, int size)
{
	int		i;
	t_llist	*curr;
	t_llist	*prev;

	if (!fd_list_tab)
		return ;
	i = -1;
	while (++i < size)
	{
		curr = *(fd_list_tab + i);
		while (curr)
		{
			prev = curr;
			curr = curr->next;
			free(prev);
		}
		*(fd_list_tab + i) = NULL;
	}
	free(fd_list_tab);
}
