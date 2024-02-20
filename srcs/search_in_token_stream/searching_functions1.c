/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:37:09 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/15 19:37:09 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

t_bool	find_logical_and(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = FALSE;
	if (token->type == T_AND)
	{
		return_value = TRUE;
	}
	return (return_value);
}

t_bool	find_logical_or(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = FALSE;
	if (token->type == T_OR)
	{
		return_value = TRUE;
	}
	return (return_value);
}

t_bool	find_logical_operator(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = find_logical_and(token);
	if (return_value == FALSE)
	{
		return_value = find_logical_or(token);
	}
	return (return_value);
}

t_bool	find_pipe(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = FALSE;
	if (token->type == T_PIPE)
	{
		return_value = TRUE;
	}
	return (return_value);
}
