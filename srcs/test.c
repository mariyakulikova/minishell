/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:38:53 by fjoestin          #+#    #+#             */
/*   Updated: 2024/08/02 16:14:42 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	test_tokens(t_token	*token)
{
	int	i = 0;

	while (token != NULL)
	{
		printf("token number: %i\n", i);
		printf("value: [%s]\n", token->value);
		printf("Quotes: [%i]\n", token->quotes);
		i++;
		token = token->next;
	}
}