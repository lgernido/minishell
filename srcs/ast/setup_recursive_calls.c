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

void	setup_new_ast_branch(t_core *core, t_ast_node *node_to_init)
{
	node_to_init = ast_new_node();
	if (node_to_init == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	node_to_init->parent = core->ast;
}

void	setup_recursive_calls(t_token_stream_node *stream_after_last_used_node,
		t_core *core)
{
	t_token_stream_node	*next_and_operator;
	t_token_stream_node	*next_or_operator;

	next_and_operator = find_logical_operator(stream_after_last_used_node, AND);
	next_or_operator = find_logical_operator(stream_after_last_used_node, OR);
	if (next_and_operator != NULL)
	{
		setup_new_ast_branch(core, core->ast->on_success);
		ft_lst_cpy(core, stream_after_last_used_node, next_and_operator, NULL);
	}
	if (next_or_operator != NULL)
	{
		setup_new_ast_branch(core, core->ast->on_failure);
		ft_lst_cpy(core, stream_after_last_used_node, next_or_operator, NULL);
	}
	ft_token_stream_clear(&stream_after_last_used_node);
	core->ast = core->ast->on_success;
	setup_ast(next_and_operator, core);
	core->ast = core->ast->parent->on_failure;
	setup_ast(next_or_operator, core);
}

/* find_begining of the new branches -- done
	 create new asts nodes
	 copy the stream in new nodes
*/	
