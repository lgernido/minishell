/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_recursive_calls.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:32:05 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/12 19:33:30 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include "clean_and_error.h"

static void	recursive_call(t_core *core, int mode)
{
	t_token_stream_node	*token_stream;
	t_ast_node			*next_node;

	next_node = return_relevant_node(core->ast, mode);
	if (next_node != NULL)
	{
		core->ast = next_node;
		detach_token_stream(&(core->ast), &token_stream);
		setup_current_node(token_stream, core);
		reset_ast(&(core->ast));
	}
}

static void	try_setup_new_nodes(t_core *core,
		t_token_stream_node *on_success,
		t_token_stream_node *on_failure)
{
	if (on_success != NULL)
	{
		setup_new_node(core, &on_success, &on_failure, SUCESS_NODE);
	}
	if (on_failure != NULL)
	{
		setup_new_node(core, &on_success, &on_failure, FAILURE_NODE);
	}
	recursive_call(core, SUCESS_NODE);
	recursive_call(core, FAILURE_NODE);
}

static void	get_token_stream_for_the_specified_branch(
		t_token_stream_node *stream_after_last_used_node,
		t_bool (*matching_function)(t_token_stream_node *token),
		t_token_stream_node **dest)
{
	t_token_stream_node	*next_searched_operator;

	next_searched_operator = find_searched_token(stream_after_last_used_node,
			matching_function);
	if (next_searched_operator != NULL)
	{
		ft_lst_cpy(next_searched_operator->next, dest, NULL);
	}
}

static void	search_token_streams_for_new_branches(
		t_token_stream_node *stream_after_last_used_node, t_core *core,
		t_token_stream_node **on_success, t_token_stream_node **on_failure)
{
	*on_success = NULL;
	*on_failure = NULL;
	get_token_stream_for_the_specified_branch(stream_after_last_used_node,
		find_logical_and, on_success);
	check_for_error(core, &stream_after_last_used_node, NULL);
	get_token_stream_for_the_specified_branch(stream_after_last_used_node,
		find_logical_or, on_failure);
	check_for_error(core, &stream_after_last_used_node, NULL);
}

void	setup_recursive_calls(t_token_stream_node *stream_after_last_used_node,
		t_core *core)
{
	t_token_stream_node	*on_success;
	t_token_stream_node	*on_failure;

	search_token_streams_for_new_branches(stream_after_last_used_node, core,
		&on_success, &on_failure);
	ft_token_stream_clear(&stream_after_last_used_node);
	try_setup_new_nodes(core, on_success, on_failure);
}
