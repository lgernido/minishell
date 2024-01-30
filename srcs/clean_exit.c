/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:37:58 by purmerinos        #+#    #+#             */
/*   Updated: 2024/01/30 16:37:59 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	ft_clean_node(t_command_node *node)
{
	if (node->fd_infile != -1)
		close(node->fd_infile);
	if (node->fd_outfile != -1)
		close(node->fd_outfile);
	if (node->infile)
		free(node->infile);
	if (node->outfile)
		free(node->outfile);
	if (node->cmd)
		ft_free_tab(node->cmd);
}

void	ft_clean_exit(t_command_node **list, int code)
{
	t_command_node	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		ft_clean_node(*list);
		free(*list);
		*list = tmp;
	}
	rl_clear_history();
	exit (code);
}
