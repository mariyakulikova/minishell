/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:24:34 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/10 17:29:43 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char **cmds_path, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	*temp;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (*(cmds_path + i))
	{
		temp = ft_strjoin(*(cmds_path + i), "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	parse_cmds(t_param *params, int argc, char **argv)
{
	int	size;
	int	shift;
	int	i;

	size = params->cmd_num;
	if (params->here_doc)
		shift = 3;
	else
		shift = 1;
	params->cmds = (char ***)malloc(sizeof(char **) * (size + 1));
	*(params->cmds + size) = NULL;
	i = 0;
	while (i < size)
	{
		*(params->cmds + i) = ft_split(*(argv + shift + i), ' ');
		if (*(params->cmds + i) == NULL)
			my_exit(params, ERR_SPLT, NULL);
		i++;
	}
}

void	set_path_value(t_param *params, char **envp)
{
	if (envp == NULL)
		my_exit(params, ERR_ENVP, NULL);
	params->path = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			params->path = *envp + 5;
			break ;
		}
		envp++;
	}
}
