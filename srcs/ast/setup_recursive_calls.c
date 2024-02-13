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

void	setup_on_success_branch(t_token_stream_node *stream_after_last_used_node, t_core *core)
{
	t_token_stream_node *on_success;
	t_token_stream_node	*stream_copy;
	t_ast_node *new_node;

	stream_copy = NULL;
	on_success = find_logical_operator(stream_after_last_used_node, AND);
	if (on_success != NULL)
	{
		ft_lst_cpy(core, on_success->next, &stream_copy, NULL);
		new_node = ast_new_node();
		if (new_node == NULL)
			ft_clean_exit(core, MALLOC);
		core->ast->on_success = new_node;
		core->ast->on_success->parent = core->ast;
		core->ast = core->ast->on_success;
		setup_ast(stream_copy, core);
		core->ast = core->ast->parent;
	}
	climb_stream_to_origin(&stream_after_last_used_node);
}

void	setup_on_failure_branch(t_token_stream_node *stream_after_last_used_node, t_core *core)
{
	t_token_stream_node *on_failure;
	t_token_stream_node	*stream_copy;
	t_ast_node *new_node;

	stream_copy = NULL;
	on_failure = find_logical_operator(stream_after_last_used_node, OR);
	if (on_failure != NULL)
	{
		ft_lst_cpy(core, on_failure->next, &stream_copy, NULL);
		new_node = ast_new_node();
		if (new_node == NULL)
			ft_clean_exit(core, MALLOC);
		core->ast->on_failure = new_node;
		core->ast->on_failure->parent = core->ast;
		core->ast = core->ast->on_failure;
		setup_ast(stream_copy, core);
		core->ast = core->ast->parent;
	}
}

void	setup_recursive_calls(t_token_stream_node *stream_after_last_used_node,
		t_core *core)
{
	if (stream_after_last_used_node == NULL)
		return ;
	setup_on_success_branch(stream_after_last_used_node, core);
	setup_on_failure_branch(stream_after_last_used_node, core);
}

/* find_begining of the new branches -- done
	 create new asts nodes
	 copy the stream in new nodes
*/	
