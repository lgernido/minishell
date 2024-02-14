/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:16:23 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/13 10:55:49 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_node	*init_node(t_command_node *node)
{
	node = malloc(sizeof(t_command_node));
	if (node)
	{
		node->fd_infile = -1;
		node->fd_outfile = -1;
		node->infile = NULL;
		node->outfile = NULL;
		node->cmd = NULL;
		node->next = NULL;
		node->prev = NULL;
	}
	return (node);
}

void	node_add_back(t_command_node **list, t_command_node *node)
{
	if (!node)
		return ;
	if (!*list)
		*list = node;
	while ((*list)->next)
		*list = (*list)->next;
	node->prev = *list;
	(*list)->next = NULL;
}

void	init_core(t_core *core)
{
	core->error_code = 0;
	core->ast = NULL;
	core->env = NULL;
	core->token_list = NULL;
}
