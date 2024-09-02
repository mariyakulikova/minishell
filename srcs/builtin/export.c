/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:13:40 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/06 22:56:23 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_export(t_data *data)
{
	int	wexport;
	int	i;
	int	j;
	int	k;
	char	*new_key;
	char	*new_value;
	t_env_lst	*list;
	
	list = data->export_list;
	wexport = get_builtin_index(data->cmd_tab, "export");
	i = 1;
	if (data->cmd_tab[wexport][1] != NULL)
	{
		//check for valid format
		while (data->cmd_tab[wexport][i])
		{
			if (valid_format(data->cmd_tab[wexport][i]) == 1)
			{
				write(2, "export: input not valid\n", 25);
				return (-1);
			}
			i++;
		}
		
	}
	i = 1;
	j = 0;
	while (data->cmd_tab[wexport][i] != NULL)
	{
		new_key = NULL;
		new_value = NULL;
		while (data->cmd_tab[wexport][i][j] != '\0' && data->cmd_tab[wexport][i][j] != '=')
		{
			new_key[j] = data->cmd_tab[wexport][i][j];
			j++;
		}
		k = 0;
		while (data->cmd_tab[wexport][i][++j] != '\0')
		{
			new_value[k] = data->cmd_tab[wexport][i][j];
			k++;
		}
		update_exp_list(list, new_key, new_value);
		if (new_value != NULL)
			update_env_list(data->lst, new_key, new_value);
		i++;
	}
	sort_list(list);
	while (list)
	{
		printf("declare -x %s", list->key);
		if (list->value != NULL)
		{
			printf("=\"%s\"", list->value);
		}
		printf("\n");
		list = list->next;
	}
	data->export_list = list;
	return (0);
}

int	valid_format(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '_' && ft_isdigit(str[i]) == 0 && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void    sort_list(t_env_lst *list)
{
    t_env_lst   *tmp;
    char *tmp_key;
    char *tmp_value;
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
	//check if exists
	//if doesn't create a new one and add to the bottom
	bool	found;
	t_env_lst	*new;

	found = false;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->key, new_key) == 0)
		{
			found = true;
			curr->value = ft_substr(new_value, 0, ft_strlen(new_value));
		}
		curr = curr->next;
	}
	if (found == false)
	{
		new = (t_env_lst *)malloc(sizeof(t_env_lst));
		new->key = ft_substr(new_key, 0, ft_strlen(new_key));
		if (new_key != NULL)
			new->value = ft_substr(new_value, 0, ft_strlen(new_value));
		else
			new->value = NULL;
		new->next = NULL;
		curr->next = new;
	}
}