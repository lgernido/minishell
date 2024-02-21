/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:21:37 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/12 12:21:37 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

static void	copy_token_stream_relevant_for_current_node(t_core *core,
		t_token_stream_node *token_stream,
		t_token_stream_node *next_logical_operator)
{
	ft_lst_cpy(token_stream, &core->ast->token_stream,
		next_logical_operator);
	check_for_error(core, &token_stream, NULL);
}

static void	check_for_parenthesis_to_trim(t_token_stream_node **token_stream)
{
	while (is_the_searched_token(*token_stream, T_PAR_OPEN) == TRUE)
	{
		discard_parenthesis(token_stream);
	}
}

static	void	setup_recursive_calls_if_needed_or_exit(t_core *core,
		t_token_stream_node **next_logical_operator,
		t_token_stream_node **current_token_stream)
{
	if (*next_logical_operator != NULL)
	{
		setup_recursive_calls(*next_logical_operator, core);
	}
	else
	{
		ft_clear_token_stream_if_needed(current_token_stream);
	}
}

void	setup_current_node(t_token_stream_node *token_stream, t_core *core)
{
	t_token_stream_node	*next_logical_operator;

	check_for_parenthesis_to_trim(&token_stream);
	next_logical_operator = find_searched_token(token_stream,
			find_logical_operator);
	copy_token_stream_relevant_for_current_node(core,
		token_stream, next_logical_operator);
	setup_recursive_calls_if_needed_or_exit(core, &next_logical_operator,
		&token_stream);
}

void	ast_init(t_token_stream_node *token_stream, t_core *core)
{
	core->ast = ast_new_node();
	if (core->ast == NULL)
	{
		clear_stream_and_exit(core, &token_stream, MALLOC);
	}
	setup_current_node(token_stream, core);
}
