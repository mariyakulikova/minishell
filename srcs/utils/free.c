
#include "../../minishell.h"

static void	free_tab(char **tab);
static void	free_env_lst(t_env_lst *list);

void	ft_free_data(t_data *data)
{
	free_env_lst(data->lst);
	free_env_lst(data->export_list);
	free_tokens(data->tokens);
	free_llist(data->fd_list_tab);
	//free built in func?how?
	free_tab(data->builtin_name);
	free_tab(data->envp);
	free_triple_tab(data->cmd_tab);
	free(data->prompt);
	//free(data->line);
	free(data->oldpwd);
}

void	free_triple_tab(char ***cmd_tab)
{
	int	i;
	int	j;

	if (!cmd_tab)
		return;
	i = 0;
	while (cmd_tab[i] != NULL)
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

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	free_env_lst(t_env_lst *list)
{
	if(!list)
		return ;
	t_env_lst	*next;
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
	free(tokens);
}

void	free_llist(t_llist **fd_list_tab)
{
	if(!fd_list_tab)
		return ;
	t_llist	*next;
	while ((*fd_list_tab) != NULL)
	{
		next = (*fd_list_tab)->next;
		free((*fd_list_tab)->key);
		free((*fd_list_tab)->value);
		free((*fd_list_tab));
		(*fd_list_tab) = next;
	}
	free(fd_list_tab);
}