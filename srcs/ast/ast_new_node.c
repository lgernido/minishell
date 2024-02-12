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

	node = malloc(sizeof (t_ast_node));
	if (node != NULL)
	{
		node->command_list = NULL;
		node->on_failure = NULL;
		node->on_success = NULL;
		node->parent = NULL;
	}
	return (node);
}

void	climb_tree_to_origin(t_ast_node **node)
{
	while ((*node)->parent != NULL)
	{
		*node = (*node)->parent;
	}
	return ;
}
