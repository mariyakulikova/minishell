/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:20:21 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/16 13:14:43 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	real_double(t_token *token, t_data *data, int red)
{
	char	*prompt;
	char	**split;
	int		j;
	t_token	*tmp;

	(void)data;
	prompt = token->value;
	j = 1;
	split = ft_split_ms(prompt, red);
	free(token->value);
	token->value = ft_strdup(split[0]);
	while (split[j] && token != NULL)
	{
		tmp = ft_new_token(split[j], &token);
		token->next = tmp;
		if (token->next)
			token = token->next;
		j++;
	}
	free_split(split);
	return (1);
}

char	**ft_split_ms(char *prompt, int red)
{
	int		wred;
	char	**split;
	int		size;

	wred = str_chr_idx(prompt, red);
	if (wred != 0 && prompt[wred + 2] != '\0')
		size = 3;
	else
		size = 2;
	split = (char **)malloc(sizeof(char *) * (size + 1));
	if (wred == 0)
	{
		split[0] = ft_substr(prompt, 0, 2);
		split[1] = ft_substr(prompt, (wred + 2), (ft_strlen(prompt) - wred));
	}
	else
	{
		split[0] = ft_substr(prompt, 0, wred);
		split[1] = ft_substr(prompt, wred, 2);
		if (size == 3)
			split[2] = ft_substr(prompt, (wred + 2),
					(ft_strlen(prompt) - wred));
	}
	split[size] = NULL;
	return (split);
}

t_type	check_redirect(t_token *tokens, t_data *data)
{
	int	check;

	check = 0;
	if (tokens->value[0] == '<' && tokens->value[1] == '\0')
		return (RED_IN);
	else if (tokens->value[0] == '>' && tokens->value[1] == '\0')
		return (RED_OUT);
	if ((tokens->value[0] == '<' && tokens->value[1] == '<')
		&& tokens->value[2] == '\0')
		return (HERE_DOC);
	if ((tokens->value[0] == '>' && tokens->value[1] == '>')
		&& tokens->value[2] == '\0')
		return (APPEND);
	check = check_redirect_helper(tokens, data, false, false);
	if (check == 0)
		return (STRING);
	else
		return (check_redirect(tokens, data));
}

int	check_redirect_helper(t_token *tokens, t_data *data, bool in_sq, bool in_dq)
{
	int		i;
	int		entered;
	char	*prompt;

	i = -1;
	entered = 0;
	prompt = ft_strdup(tokens->value);
	while (prompt[++i] != '\0')
	{
		if (prompt[i] == SINGLE_QUOTE && !in_dq)
			in_sq = !in_sq;
		else if (prompt[i] == DOUBLE_QUOTE && !in_sq)
			in_dq = !in_dq;
		if ((prompt[i] == '<' || prompt[i] == '>') && (tokens->type != APPEND
				&& tokens->type != HERE_DOC) && !in_sq && !in_dq)
			entered = real_red(tokens, prompt[i]);
		if (((prompt[i] == '<' && prompt[i + 1] == '<' ) || (prompt[i] == '>'
					&& prompt[i + 1] == '>')) && !in_sq && !in_dq)
		{
			entered = real_double(tokens, data, prompt[i]);
			break ;
		}
	}
	free(prompt);
	return (entered);
}

int	real_red(t_token *token, int red)
{
	char	**split;
	int		wred;
	int		j;
	t_token	*tmp;

	j = 1;
	wred = str_chr_idx(token->value, red);
	if (token->value[wred + 1] == red || token->value[wred + 1] == '\0')
		return (1);
	split = ft_split_red_ms(token->value, wred);
	free(token->value);
	token->value = ft_strdup(split[0]);
	while (split[j] != NULL && token != NULL)
	{
		tmp = ft_new_token(split[j], &token);
		token->next = tmp;
		if (token->next)
			token = token->next;
		j++;
	}
	free_split(split);
	return (1);
}
