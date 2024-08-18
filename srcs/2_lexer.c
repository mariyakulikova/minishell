
#include "../minishell.h"

/* t_type	check_heredoc(t_token *tokens, t_data *data) //should be this token specific
{
	int	i;
	bool	in_squotes;
	bool	in_dquotes;

	i = 0;
	in_squotes = false;
	in_dquotes = false;
	if (tokens->value[0] == '<' && tokens->value[1] == '<' && tokens->value[2] == '\0')
		return (HERE_DOC);
	while (tokens->value[i])
	{
		if (tokens->value[i] == SINGLE_QUOTE && !in_dquotes)
			in_squotes = !in_squotes;
		else if (tokens->value[i] == DOUBLE_QUOTE && !in_squotes)
			in_dquotes = !in_dquotes;
		if ((tokens->value[i] == '<' && tokens->value[i + 1] == '<') && !in_squotes && !in_dquotes)
			real_heredoc(tokens, data);
		i++;
	}
	return(STRING);
}

void	real_heredoc(t_token *token, t_data *data)
{
	char	*prompt;
	char	**split;
	int		wheredoc;
	int		size;
	int		j = 1;
	t_token	*tmp;// will i have to initialize?

	prompt = token->value;
	wheredoc = ft_strnstr(prompt, "<<", 2);
	if (prompt[wheredoc] != 0 && prompt[wheredoc + 2] != '\0')
	{
		split = (char **)malloc(sizeof(char *) * 4);
		size = 3;
	}
	else
	{
		split = (char **)malloc(sizeof(char *) * 3);
		size = 2;
	}
	if (wheredoc == 0)
	{
		split[0] = ft_strdup("<<");
		split[1] = ft_substr(prompt, 2, (ft_strlen(prompt) - 2));
	}
	else
	{
		split[0] = ft_substr(prompt, 0, wheredoc);
		split[1] = ft_strdup("<<");
		if (prompt[wheredoc + 2])
		{
			split[2] = ft_substr(prompt, (wheredoc + 2), (ft_strlen(prompt) - (wheredoc + 1))); 
		}
	}
	split[size] = NULL;
	token->value = ft_strdup(split[0]);
	while (split[j] && token != NULL)
	{
		tmp = ft_new_token(split[j]);
		tmp->prev = token;
		if (token->next)
		{
			tmp->next = token->next;
			token->next->prev = tmp;
		}
		else
			tmp->next = NULL;
		token->next = tmp;
		if (token->next)
			token = token->next;
		j++;
	}
	processing(data);
} */

t_type	check_redirect(t_token *tokens, t_data *data) //should be this token specific
{
	int	i;
	bool	in_squotes;
	bool	in_dquotes;
	i = 0;
	in_squotes = false;
	in_dquotes = false;
	if ((tokens->value[0] == '<' || tokens->value[0] == '>') && tokens->value[1] == '\0')
		return (RED);
	while (tokens->value[i])
	{
		if (tokens->value[i] == SINGLE_QUOTE && !in_dquotes)
			in_squotes = !in_squotes;
		else if (tokens->value[i] == DOUBLE_QUOTE && !in_squotes)
			in_dquotes = !in_dquotes;
		if ((tokens->value[i] == '<' || tokens->value[i] == '>') && !in_squotes && !in_dquotes)
			real_red(tokens, data, tokens->value[i]);
		i++;
	}
	return(STRING);
}

void	real_red(t_token *token, t_data *data, int red)
{
	char	*prompt;
	char	**split;
	int		wred;
	int		size;
	int		j = 1;
	t_token	*tmp;

	prompt = token->value;
	wred = str_chr_idx(prompt, red);
	if (wred != 0 && prompt[wred + 1] != '\0')
	{
		split = (char **)malloc(sizeof(char *) * 4);
		size = 3;
	}
	else
	{
		split = (char **)malloc(sizeof(char *) * 3);
		size = 2;
	}
	if(size == 2)
	{
		if(wred == 0)
			wred++;
		split[0] = ft_substr(prompt, 0, wred);
		split[1] = ft_substr(prompt, wred, (ft_strlen(prompt) - wred));
	}
	else
	{
		split[0] = ft_substr(prompt, 0, wred);
		split[1] = ft_substr(prompt, wred, 1);
		split[2] = ft_substr(prompt, (wred + 1), (ft_strlen(prompt) - wred));
	}
	split[size] = NULL;
	token->value = ft_strdup(split[0]);
	while (split[j] && token != NULL)
	{
		tmp = ft_new_token(split[j]);
		tmp->prev = token;
		if (token->next)
		{
			tmp->next = token->next;
			token->next->prev = tmp;
		}
		else
			tmp->next = NULL;
		token->next = tmp;
		if (token->next)
			token = token->next;
		j++;
	}
	processing(data);
}
