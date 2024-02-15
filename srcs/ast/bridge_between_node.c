/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_between_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:34:26 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/15 15:38:33 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include <readline/readline.h>

t_ast_node	*return_relevant_node(t_ast_node *node, int mode)
{
	t_ast_node	*node_to_return;

	if (match_mode_condition(mode, SUCESS_NODE) == TRUE)
	{
		node_to_return = node->on_success;
	}
	else
	{
		node_to_return = node->on_failure;
	}
	return (node_to_return);
}

static t_token_stream_node	*return_relevant_stream(
		t_token_stream_node *on_success,
		t_token_stream_node *on_failure, int mode)
{
	t_token_stream_node	*stream_to_return;

	if (match_mode_condition(mode, SUCESS_NODE) == TRUE)
	{
		stream_to_return = on_success;
	}
	else
	{
		stream_to_return = on_failure;
	}
	return (stream_to_return);
}

void	setup_new_node(t_core *core, t_token_stream_node **on_success,
		t_token_stream_node **on_failure, int mode)
{
	t_ast_node			*relevant_node;
	t_token_stream_node	*relevant_stream;
	{
		ast_add_back(&(core->ast), mode);
		check_for_error(core, on_success, on_failure);
		relevant_node = return_relevant_node(core->ast, mode);
		relevant_stream = return_relevant_stream(*on_success,
				*on_failure, mode);
		attach_token_stream(&relevant_node, &relevant_stream);
	}
}
