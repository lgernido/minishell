/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_handling_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:45:13 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/15 16:45:13 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

void	attach_token_stream(t_ast_node **node, t_token_stream_node **to_attach)
{
	(*node)->token_stream = *to_attach;
	*to_attach = NULL;
}

void	detach_token_stream(t_ast_node **node, t_token_stream_node **to_attach)
{
	*to_attach = (*node)->token_stream;
	(*node)->token_stream = NULL;
}

void	reset_ast(t_ast_node **node)
{
	*node = (*node)->parent;
}
