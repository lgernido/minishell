/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:07:09 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 19:07:10 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean_and_error.h"

void	close_if_open(int *fd)
{
	if (*fd != -1)
	{
		close (*fd);
		*fd = -1;
	}
	return ;
}

void	ft_clean_node(t_command_node *node)
{
	close_if_open(&node->fd_infile);
	close_if_open(&node->fd_outfile);
	close_if_open(&node->pipe[READ_ENTRY]);
	close_if_open(&node->pipe[WRITE_ENTRY]);
	close_if_open(&node->saved_infile);
	close_if_open(&node->saved_outfile);
	ft_clear_token_stream_if_needed(&node->redirections);
	if (node->here_doc != NULL)
	{
		free(node->here_doc);
	}
	if (node->cmd != NULL)
	{
		// IS ERROR PRONE !! ARRAY CAN BE NULL. WILL HANDLE IT LATER
		ft_free_tab(node->cmd);
	}
}

void	climb_command_list_to_origin(t_command_node **list)
{
	while ((*list)->prev != NULL)
	{
		*list = (*list)->prev;
	}
}

void	ft_command_clear(t_command_node **list)
{
	t_command_node	*tmp;

	climb_command_list_to_origin(list);
	while (*list)
	{
		tmp = (*list)->next;
		ft_clean_node(*list);
		free(*list);
		*list = tmp;
	}
}

