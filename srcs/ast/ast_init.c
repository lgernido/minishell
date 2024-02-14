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
	ft_lst_cpy(core, token_stream, &core->ast->token_stream,
		next_logical_operator);
}

static void	check_for_parenthesis_to_trim(t_token_stream_node **token_stream)
{
	if (is_the_searched_token(*token_stream, OPEN_PARENTHESIS) == TRUE)
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
	next_logical_operator = find_logical_operator(token_stream, ANY);
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
		clear_stream_and_exit(core, token_stream, MALLOC);
	}
	setup_current_node(token_stream, core);
}

/* So : - go trough token_stream till logical opertor -- good
				- copy in the node from start to this point -- good 
				- setup both recursivity calls
				- free token stream
				- call recursivity
*/
