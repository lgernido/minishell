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

t_bool	is_searched_operator(t_token_stream_node *node, const int mode)
{
	t_bool				return_value;

	return_value = FALSE;
	if (match_mode_condition(mode, AND) == TRUE)
	{
		return_value = is_the_searched_token(node, LOGICAL_AND);
	}
	if (return_value == FALSE && match_mode_condition(mode, OR))
	{
		return_value = is_the_searched_token(node, LOGICAL_OR);
	}
	return (return_value);
}

void	discard_parenthesis(t_token_stream_node **token_stream)
{
	t_token_stream_node	*iterator;

	*token_stream = (*token_stream)->next;
	ft_free_node((*token_stream)->prev);
	(*token_stream)->prev = NULL;
	iterator = *token_stream;
	while (is_the_searched_token(iterator, CLOSE_PARENTHESIS) != TRUE)
	{
		if (is_the_searched_token(*token_stream, OPEN_PARENTHESIS) == TRUE)
		{
			jump_above_parenthesis(token_stream);
		}
		iterator = iterator->next;
	}
	ft_pop_node(&iterator);
	return ;
}

t_token_stream_node	*find_logical_operator(t_token_stream_node *token_stream,
		int mode)
{
	t_token_stream_node	*next_logical_operator;

	next_logical_operator = NULL;
	while (token_stream != NULL)
	{
		if (is_the_searched_token(token_stream, OPEN_PARENTHESIS) == TRUE)
		{
			jump_above_parenthesis(&token_stream);
		}
		else if (is_searched_operator(token_stream, mode) == TRUE)
		{
			next_logical_operator = token_stream;
			break ;
		}
		token_stream = token_stream->next;
	}
	return (next_logical_operator);
}
