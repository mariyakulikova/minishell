/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:38:53 by fjoestin          #+#    #+#             */
/*   Updated: 2024/08/08 14:34:03 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	test_tokens(t_token	*token)
{
	int	i = 0;

	while (token != NULL)
	{
		printf("token number: %i\n", i);
		printf("token index: [%i]\n", token->index);
		printf("value: [%s]\n", token->value);
		printf("Quotes: [%i]\n", token->quotes);
		printf("Type: [%u]\n", token->type);
		i++;
		token = token->next;
	}
}

void	test_list(t_env_lst *list)
{
	while (list != NULL)
	{
		printf("key: [%s] value: [%s]\n", list->key, list->value);
		list = list->next;	
	}
}