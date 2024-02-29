/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_base_funct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:01:51 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/22 19:01:55 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	init_node(t_command_node *node)
{
	ft_bzero(node, sizeof(t_command_node));
	node->pipe[READ_ENTRY] = -1;
	node->pipe[WRITE_ENTRY] = -1;
	node->fd_infile = -1;
	node->fd_outfile = -1;
	return ;
}

t_command_node	*create_command_list_node(void)
{
	t_command_node	*new_node;

	new_node = malloc(sizeof(t_command_node));
	if (new_node != NULL)
	{
		init_node(new_node);
	}
	return (new_node);
}

void	command_node_add_back(t_command_node **command_list,
		t_command_node *new_node)
{
	t_command_node	*tmp;

	if (new_node == NULL || command_list == NULL)
	{
		return ;
	}
	if (*command_list == NULL)
	{
		*command_list = new_node;
		return ;
	}
	tmp = *command_list;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new_node;
	tmp->next->prev = tmp;
	return ;
}

void	get_last_command_node(t_command_node **command_list)
{
	if (command_list == NULL || *command_list == NULL)
	{
		return ;
	}
	while ((*command_list)->next != NULL)
	{
		*command_list = (*command_list)->next;
	}
	return ;
}

void	update_command_list(t_core *core)
{
	t_command_node	*new_node;

	new_node = create_command_list_node();
	if (new_node == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	command_node_add_back(&core->ast->command_list, new_node);
	get_last_command_node(&core->ast->command_list);
	return ;
}
