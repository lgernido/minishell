/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:37:58 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/13 10:55:56 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_command_clear(t_command_node **list)
{
	t_command_node	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		ft_clean_node(*list);
		free(*list);
		*list = tmp;
	}
}

void	ft_clean_exit(t_core *core, int code)
{
	if (core->env)
		ft_free_tab(core->env);
	if (core->command_list)
		ft_command_clear(&core->command_list);
	if (core->token_list)
		ft_clear_token_list(&core->token_list, free);
	rl_clear_history();
	exit(code);
}
