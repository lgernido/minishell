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

void	copy_token_stream_relevant_for_current_node(t_core *core,
		t_token_stream_node *token_stream,
		t_token_stream_node *next_logical_operator)
{
	ft_lst_cpy(core, token_stream, &core->ast->token_stream,
		next_logical_operator);
}

void	check_for_parenthesis_to_trim(t_token_stream_node **token_stream)
{
	if (is_the_searched_token(*token_stream, OPEN_PARENTHESIS) == TRUE)
	{
		discard_parenthesis(token_stream);
	}
}

void	setup_ast(t_token_stream_node *token_stream, t_core *core)
{
	t_token_stream_node	*next_logical_operator;

	check_for_parenthesis_to_trim(&token_stream);
	next_logical_operator = find_logical_operator(token_stream, ANY);
	copy_token_stream_relevant_for_current_node(core,
		token_stream, next_logical_operator);
	setup_recursive_calls(next_logical_operator, core);
}

void	ast_init(t_token_stream_node *token_stream, t_core *core)
{
	core->ast = ast_new_node();
	if (core->ast == NULL)
		ft_clean_exit(core, MALLOC);
	setup_ast(token_stream, core);
}

/* So : - go trough token_stream till logical opertor -- good
				- copy in the node from start to this point -- good 
				- setup both recursivity calls
				- free token stream
				- call recursivity
*/
