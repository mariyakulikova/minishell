/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:13:40 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/12 16:22:26 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_list(t_env_lst *list);
static void	ft_export_helper(t_data *data, int wexport, int	i);

int	ft_export(t_data *data, char **cmd_tab)
{
	int	wexport;
	int	i;
	(void)cmd_tab;
	wexport = get_builtin_index(data->cmd_tab, "export");
	i = 1;
	if (data->cmd_tab[wexport][i] == NULL)
	{
		print_list(data->export_list);
		return (0);
	}
	while (data->cmd_tab[wexport][i] != NULL)
	{
		if (valid_format(data->cmd_tab[wexport][i]) == 1)
		{
			write(2, "export: input not valid\n", 25);
			return (1);
		}
		i++;
	}	
	ft_export_helper(data, wexport, i);
	return (0);
}

static void	ft_export_helper(t_data *data, int wexport, int	i)
{
	char	*new_key;
	char	*new_value;
	int	j;
	
	i = 1;
	while (data->cmd_tab[wexport][i] != NULL)
	{
		new_value = NULL;
		if(ft_strchr(data->cmd_tab[wexport][i], '=') != NULL)
		{
			j = (((int)ft_strlen(data->cmd_tab[wexport][i])) - ((int)ft_strlen(ft_strchr(data->cmd_tab[wexport][i], '='))));
			new_key = ft_substr(data->cmd_tab[wexport][i], 0, j);
			if (data->cmd_tab[wexport][i][++j] != '\0')
			{
				new_value = ft_substr(data->cmd_tab[wexport][i], j, ft_strlen(ft_strchr(data->cmd_tab[wexport][i], '=')) - 1);
				update_env_list(data->lst, new_key, new_value);
			}
		}
		else
			new_key = ft_strdup(data->cmd_tab[wexport][i]);
		update_exp_list(data->export_list, new_key, new_value);
		i++;
		free(new_key);
		free(new_value);
	}
}

static void	print_list(t_env_lst *list)
{
	sort_list(list);
	while (list)
	{
		printf("declare -x %s", list->key);
		if (list->value != NULL)
			printf("=\"%s\"", list->value);
		printf("\n");
		list = list->next;
	}	
}
int	valid_format(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (1);
	while (str[i] != '=' && str[i])
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] != '\0')
	{
		while (str[++i])
		{
			if (ft_isalpha(str[i]) == 0 && str[i] != '_' && ft_isdigit(str[i]) == 0 && str[i] != ' ' && str[i] != '-')
				return (1);
		}
	}
	return (0);
}

void	sort_list(t_env_lst *list)
{
	t_env_lst	*tmp;
	char		*tmp_key;
	char		*tmp_value;
	
	tmp = list;
	while (list->next)
	{
		if (ft_strcmp(list->key, list->next->key) > 0)
		{
			tmp_key = list->key;
			tmp_value = list->value;
			list->key = list->next->key;
			list->value = list->next->value;
			list->next->key = tmp_key;
			list->next->value = tmp_value;
			list = tmp;
		}
		else
			list = list->next;
	}
}

void	update_exp_list(t_env_lst *curr, char *new_key, char *new_value)
{
	bool	found;
	t_env_lst	*new;

	found = false;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->key, new_key) == 0)
		{
			found = true;
			if(new_value != NULL)
				curr->value = ft_substr(new_value, 0, ft_strlen(new_value));
		}
		curr = curr->next;
	}
	if (found == false && ft_strcmp(curr->key, new_key) != 0)
	{
		new = new_env(new_key, new_value);
		curr->next = new;
	}
	else
		if(new_value != NULL)
			curr->value = ft_substr(new_value, 0, ft_strlen(new_value));
}
t_env_lst	*new_env(char *new_key, char *new_value)
{
	t_env_lst *new;
	
	new = (t_env_lst *)malloc(sizeof(t_env_lst));
	if (!new)
		perror("Error malloc\n");
	new->key = ft_substr(new_key, 0, ft_strlen(new_key));
	if (new_value != NULL)
		new->value = ft_substr(new_value, 0, ft_strlen(new_value));
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}
