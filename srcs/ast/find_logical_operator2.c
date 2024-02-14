/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_logical_operator2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:00:04 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/12 17:00:22 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"

t_bool	match_type_condition(const t_token_type type,
		const t_token_type searched_type)
{
	t_bool	ret_value;

	ret_value = FALSE;
	if (type == searched_type)
	{
		ret_value = TRUE;
	}
	return (ret_value);
}

t_bool	match_mode_condition(const int mode, const int searched_mode)
{
	t_bool	return_value;

	return_value = FALSE;
	if (mode == searched_mode || mode == ANY)
	{
		return_value = TRUE;
	}
	return (return_value);
}

t_bool	is_the_searched_token(const t_token_stream_node *token,
		const t_token_type searched_type)
{
	t_bool	return_value;

	return_value = match_type_condition(token->type, searched_type);
	return (return_value);
}

t_token_stream_node	*jump_above_parenthesis(t_token_stream_node *token)
{
	token = token->next;
	while (is_the_searched_token(token, T_PAR_CLOSE) == FALSE)
	{
		jump_above_parenthesis_if_needed(&token);
		token = token->next;
	}
	return (token->next);
}

void	jump_above_parenthesis_if_needed(t_token_stream_node **token_stream)
{
	if (is_the_searched_token(*token_stream, T_PAR_OPEN) == TRUE)
	{
		*token_stream = jump_above_parenthesis(*token_stream);
	}
}
