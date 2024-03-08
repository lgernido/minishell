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

void	update_stream_if_needed(t_token_stream_node **token_stream)
{
	if (*token_stream != NULL)
	{
		*token_stream = (*token_stream)->next;
	}
}

void	discard_parenthesis(t_token_stream_node **token_stream)
{
	t_token_stream_node	*iterator;
	size_t				parenthesis_counter;

	parenthesis_counter = 1;
	free_first_parenthesis(token_stream);
	iterator = *token_stream;
	while (iterator != NULL)
	{
		parenthesis_counter += check_for_parenthesis(iterator, T_PAR_OPEN);
		check_for_closing_parenthesis(&iterator, &parenthesis_counter);
		update_stream_if_needed(&iterator);
	}
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
