/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_and_parse_envp.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:16:23 by purmerinos        #+#    #+#             */
/*   Updated: 2024/01/30 16:16:23 by purmerinos       ###   ########.fr       */
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
	core->command_list = NULL;
	core->env = NULL;
}
