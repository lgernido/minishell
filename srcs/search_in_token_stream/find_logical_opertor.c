/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream_copy_till_operato.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:57 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/12 15:52:57 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"

static void	update_stream_if_needed(t_token_stream_node **token_stream)
{
	if (*token_stream != NULL)
	{
		*token_stream = (*token_stream)->next;
	}
}

void	discard_parenthesis(t_token_stream_node **token_stream)
{
	t_token_stream_node	*iterator;

	*token_stream = (*token_stream)->next;
	ft_free_node(&(*token_stream)->prev);
	(*token_stream)->prev = NULL;
	iterator = *token_stream;
	while (is_the_searched_token(iterator, T_PAR_CLOSE) != TRUE)
	{
		if (is_the_searched_token(*token_stream, T_PAR_OPEN) == TRUE)
		{
			jump_above_parenthesis_if_needed(&iterator);
		}
		if (iterator->next != NULL)
			iterator = iterator->next;
	}
	ft_del_node(&iterator);
	return ;
}

t_token_stream_node	*find_searched_token(t_token_stream_node *token_stream,
		t_bool (*matching_function)(t_token_stream_node *token))
{
	t_token_stream_node	*next_logical_operator;

	next_logical_operator = NULL;
	while (token_stream != NULL)
	{
		jump_above_parenthesis_if_needed(&token_stream);
		if (token_stream != NULL && matching_function(token_stream) == TRUE)
		{
			next_logical_operator = token_stream;
			break ;
		}
		update_stream_if_needed(&token_stream);
	}
	return (next_logical_operator);
}
