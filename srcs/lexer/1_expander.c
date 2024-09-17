/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:54:19 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/17 12:33:12 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_key(char c)
{
	return (c == '?' || c == '_' || ft_isalnum(c));
}

static char	*get_key(char *str, int i)
{
	int	j;

	j = i + 1;
	if (str[j] == '?')
		return (ft_strdup("?"));
	while (str[j])
	{
		if (ft_isalnum(str[j]) || str[j] == '_')
			j++;
		else
			break ;
	}
	return (ft_substr(str, i + 1, j - i - 1));
}

char	*get_value(char *key, t_data *data)
{
	t_env_lst	*var;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(data->exit_status));
	var = get_var_by_key(data->lst, key);
	if (var)
		return (ft_strdup((char *)var->value));
	else
		return (NULL);
}

static char	*replace_key_with_val(char *str, char *key, char *val, int i)
{
	char	*chunk;
	char	*chunk2;
	char	*temp;

	chunk = ft_substr(str, 0, i);
	chunk2 = ft_substr(str, i + ft_strlen(key) + 1, ft_strlen(str) - i);
	temp = str;
	str = ft_strjoin(chunk, val);
	free(temp);
	temp = str;
	str = ft_strjoin(str, chunk2);
	free(temp);
	free(chunk);
	free(chunk2);
	return (str);
}

char	*expand_dollar(char *str, int *i, t_data *data)
{
	char	*val;
	char	*key;

	(void) data;
	if (!is_key(str[*i + 1]))
		return (str);
	key = get_key(str, *i);
	val = get_value(key, data);
	if (val)
	{
		str = replace_key_with_val(str, key, val, *i);
		*i += ft_strlen(val) - 1;
	}
	else
	{
		ft_memmove(str + *i, str + *i + ft_strlen(key) + 1, \
					ft_strlen(str) - *i - ft_strlen(key));
		(*i)--;
	}
	free(key);
	free(val);
	return (str);
}
