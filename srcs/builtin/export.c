/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:13:40 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/14 16:31:39 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_list(t_env_lst *list);
static void	ft_export_helper(t_data *data, char **cmd_tab, int i);

int	ft_export(t_data *data, char **cmd_tab)
{
	int	i;

	i = 1;
	if (cmd_tab[i] == NULL)
	{
		print_list(data->export_list);
		return (0);
	}
	while (cmd_tab[i] != NULL)
	{
		if (valid_format(cmd_tab[i]) == 1)
		{
			write(2, "export : not a valid identifier\n", 33);
			return (1);
		}
		i++;
	}
	ft_export_helper(data, cmd_tab, i);
	return (0);
}

static void	ft_export_helper(t_data *data, char **cmd_tab, int i)
{
	char	*new_key;
	char	*new_value;
	int		j;

	i = 1;
	while (cmd_tab[i] != NULL)
	{
		new_value = NULL;
		if (ft_strchr(cmd_tab[i], '=') != NULL)
		{
			j = ((ft_strlen(cmd_tab[i])) - (ft_strlen(ft_strchr(cmd_tab[i], '='))));
			new_key = ft_substr(cmd_tab[i], 0, j);
			if (cmd_tab[i][++j] != '\0')
			{
				new_value = ft_substr(cmd_tab[i], j, ft_strlen(ft_strchr(cmd_tab[i], '=')) - 1);
				update_env_list(data->lst, new_key, new_value);
			}
		}
		else
			new_key = ft_strdup(cmd_tab[i]);
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
			if (ft_isalpha(str[i]) == 0 && str[i] != '_'
				&& ft_isdigit(str[i]) == 0 && str[i] != ' ' && str[i] != '-')
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
