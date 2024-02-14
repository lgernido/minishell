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
#include <stdio.h>

void	setup_new_branch(t_core *core,
		t_token_stream_node *stream_for_next_node, int mode)
{
	ast_add_back(&core->ast, mode);
	if (errno == ENOMEM)
	{
		clear_stream_and_exit(core, stream_for_next_node, MALLOC);
	}
	if (match_mode_condition(mode, SUCESS_NODE) == TRUE)
	{
		core->ast = core->ast->on_success;
		setup_current_node(stream_for_next_node, core);
		core->ast = core->ast->parent;
	}
	else
	{
		core->ast = core->ast->on_failure;
		setup_current_node(stream_for_next_node, core);
		core->ast = core->ast->parent;
	}
}

void	setup_new_branches(t_core *core, t_token_stream_node *on_success,
		t_token_stream_node *on_failure)
{
	if (on_success != NULL)
	{
		setup_new_branch(core, on_success, SUCESS_NODE);
	}
	if (on_failure != NULL)
	{
		setup_new_branch(core, on_failure, FAILURE_NODE);
	}
}

void	get_token_stream_for_the_specified_branch(
		t_token_stream_node *stream_after_last_used_node,
		t_core *core, int mode, t_token_stream_node **dest)
{
	t_token_stream_node	*next_searched_operator;

	next_searched_operator = find_logical_operator
		(stream_after_last_used_node, mode);
	if (next_searched_operator != NULL)
	{
		ft_lst_cpy(core, next_searched_operator->next, dest, NULL);
	}
}

void	get_token_streams_for_new_branches(
		t_token_stream_node *stream_after_last_used_node, t_core *core,
		t_token_stream_node **on_success, t_token_stream_node **on_failure)
{
	*on_success = NULL;
	*on_failure = NULL;
	get_token_stream_for_the_specified_branch(stream_after_last_used_node,
		core, AND, on_success);
	get_token_stream_for_the_specified_branch(stream_after_last_used_node,
		core, OR, on_failure);
}

void	setup_recursive_calls(t_token_stream_node *stream_after_last_used_node,
		t_core *core)
{
	t_token_stream_node	*on_success;
	t_token_stream_node	*on_failure;

	get_token_streams_for_new_branches(stream_after_last_used_node, core,
		&on_success, &on_failure);
	ft_token_stream_clear(&stream_after_last_used_node);
	setup_new_branches(core, on_success, on_failure);
}

/* find_begining of the new branches -- done
	 create new asts nodes
	 copy the stream in new nodes
*/	
