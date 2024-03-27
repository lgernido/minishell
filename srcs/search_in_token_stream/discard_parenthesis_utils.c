/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discard_parenthesis_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:04:15 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/21 15:04:15 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include "clean_and_error.h"

size_t	check_for_parenthesis(t_token_stream_node *node,
		t_token_type searched)
{
	size_t	return_value;

	return_value = 0;
	if (is_the_searched_token(node, searched))
	{
		++return_value;
	}
	return (return_value);
}

void	check_for_closing_parenthesis(t_token_stream_node **node,
		size_t *parenthesis_counter)
{
	*parenthesis_counter -= check_for_parenthesis(*node, T_PAR_CLOSE);
	if (*parenthesis_counter == 0)
	{
		ft_del_node(node);
	}
}

void	free_first_parenthesis(t_token_stream_node **token_stream)
{
	*token_stream = (*token_stream)->next;
	ft_free_node(&(*token_stream)->prev);
	(*token_stream)->prev = NULL;
}
