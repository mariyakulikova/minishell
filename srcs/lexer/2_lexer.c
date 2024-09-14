/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:20:21 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/14 16:30:44 by fjoestin         ###   ########.fr       */
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
int	check_redirect_helper(t_token *tokens, t_data *data);

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
	check = check_redirect_helper(tokens, data);
	if (check == 0)
		return (STRING);
	else
		return (check_redirect(tokens, data));
}

int	check_redirect_helper(t_token *tokens, t_data *data)
{
	int		i;
	bool	in_squotes;
	bool	in_dquotes;
	int		entered;

	in_squotes = false;
	in_dquotes = false;
	i = 0;
	entered = 0;
	char *prompt = ft_strdup(tokens->value);
	while (prompt[i] != '\0')
	{
		if (prompt[i] == SINGLE_QUOTE && !in_dquotes)
			in_squotes = !in_squotes;
		else if (prompt[i] == DOUBLE_QUOTE && !in_squotes)
			in_dquotes = !in_dquotes;
		if ((prompt[i] == '<' || prompt[i] == '>') && (tokens->type != APPEND && tokens->type != HERE_DOC) && !in_squotes && !in_dquotes)
			entered = real_red(tokens, prompt[i]);
		if (((prompt[i] == '<' && prompt[i + 1] == '<' )||( prompt[i] == '>' && prompt[i + 1] == '>')) && !in_squotes && !in_dquotes)
		{
			entered = real_double(tokens, data, prompt[i]);
			break ;
		}
		i++;
	}
	free(prompt);
	return (entered);
}


int	real_red(t_token *token, int red)
{
	char	**split;
	int		wred;
	int		j = 1;
	t_token	*tmp;

	wred = str_chr_idx(token->value, red);
	if(token->value[wred + 1] == red || token->value[wred + 1] == '\0')
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
char	**ft_split_red_ms(char *prompt, int wred)
{
	int		size;
	char	**split;

	if (wred != 0 && prompt[wred + 1] != '\0')
		size = 3;
	else
		size = 2;
	split = (char **)malloc(sizeof(char *) * (size + 1));
	if(wred == 0)
	{
		split[0] = ft_substr(prompt, 0, 1);
		split[1] = ft_substr(prompt, (wred + 1), (ft_strlen(prompt) - wred));
	}
	else
	{
		split[0] = ft_substr(prompt, 0, wred);
		split[1] = ft_substr(prompt, wred, 1);
		if (size == 3)
			split[2] = ft_substr(prompt, (wred + 1), (ft_strlen(prompt) - wred));
	}
	split[size] = NULL;
	return (split);
}

void	check_types(t_data *data)
{
	t_token *token;

	token = data->tokens;
	while (token != NULL)
	{
		if (token->type == PIPE && (token->index == 0 || token->index == (data->n_tokens - 1)))
			ft_exit_err("pipe doesn't work\n", data);
		if (token->type != STRING && ((token->index == 0 && (data->n_tokens == 1)) || token->index == (data->n_tokens - 1)))
			ft_exit_err("unexpected syntax\n", data);
		if (token->type == PIPE && token->next->type == PIPE)
			ft_exit_err("2 pipes\n", data);
		if ((token->type != STRING && token->type != PIPE) && token->next->type != STRING)
			ft_exit_err("unexpected syntax\n", data);
		token = token->next;
	}
}
