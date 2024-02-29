/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:26:21 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/12 15:26:23 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

t_ast_node	*ast_new_node(void)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof (t_ast_node));
	return (node);
}

void	ast_add_back(t_ast_node **ast, int mode)
{
	t_ast_node	*new_node;

	new_node = ast_new_node();
	if (new_node == NULL)
	{
		return ;
	}
	new_node->parent = *ast;
	if (match_mode_condition(mode, SUCESS_NODE))
	{
		(*ast)->on_success = new_node;
	}
	else
	{
		(*ast)->on_failure = new_node;
	}
	return ;
}

void	climb_tree_to_origin(t_ast_node **node)
{
	while ((*node)->parent != NULL)
	{
		*node = (*node)->parent;
	}
	return ;
}
