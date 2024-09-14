/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:52:17 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/14 01:37:11 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

static char	*shift_str(char *str, int i, int j)
{
	char	*chunk;
	char	*chunk2;
	char	*chunk3;
	char	*temp;

	chunk = ft_substr(str, 0, j);
	chunk2 = ft_substr(str, j + 1, i - j - 1);
	chunk3 = ft_strdup(str + i + 1);
	temp = chunk;
	chunk = ft_strjoin(chunk, chunk2);
	free(temp);
	free(chunk2);
	temp = chunk;
	chunk = ft_strjoin(chunk, chunk3);
	free(temp);
	free(chunk3);
	free(str);
	return (chunk);
}

static char	*expand_single_qoutes(char *str, int *i)
{
	int	j;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	if ((size_t)(*i) == ft_strlen(str))
		return (str);
	str = shift_str(str, *i, j);
	*i -= 2;
	return (str);
}

static char	*expand_double_qoutes(char *str, int *i, t_data *data)
{
	int	j;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '$')
			str = expand_dollar(str, i, data);
		if (str[*i] == '\"')
			break ;
	}
	if ((size_t)(*i) == ft_strlen(str))
		return (str);
	str = shift_str(str, *i, j);
	*i -= 2;
	return (str);
}

void	expander(t_token *tokens, t_data *data)
{
	int		i;
	t_token *curr;
	// t_token	*tmp;
	char	*str;

	curr = tokens;
	while (curr)
	{
		i = -1;
		str = curr->value;
		while (str[++i])
		{
			if (str[i] == '\'')
				str = expand_single_qoutes(str, &i);
			if (str[i] == '\"')
				str = expand_double_qoutes(str, &i, data);
			if (str[i] == '$')
				str = expand_dollar(str, &i, data);
		}
		curr->value = str;
		curr = curr->next;
	}
	update_index(data->tokens, data);
}
