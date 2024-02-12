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

void	setup_ast(t_token_stream_node *token_stream, t_core *core)
{
	t_token_stream_node	*next_logical_operator;

	if (core->ast == NULL)
		return ;
	next_logical_operator = find_logical_operator(token_stream, ANY);
	ft_lst_cpy(core, token_stream, core->ast->token_stream,
		next_logical_operator);
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
