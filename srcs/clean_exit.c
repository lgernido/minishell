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

void	ft_token_stream_clear(t_token_stream_node **token_stream)
{
	t_token_stream_node	*tmp;

	while (*token_stream != NULL)
	{
		tmp = (*token_stream)->next;
		free((*token_stream)->value);
		free(*token_stream);
		*token_stream = tmp;
	}
}

void	ft_ast_clear(t_ast_node **node)
{
	if (*node == NULL)
		return ;
	ft_ast_clear(&(*node)->on_success);
	ft_ast_clear(&(*node)->on_failure);
	if ((*node)->command_list != NULL)
		ft_command_clear(&(*node)->command_list);
	if ((*node)->token_stream)
		ft_token_stream_clear(&(*node)->token_stream);
}

void	ft_clean_exit(t_core *core, int code)
{
	if (core->envp)
		ft_free_tab(core->envp);
	if (core->ast)
		ft_ast_clear(&core->ast);
	rl_clear_history();
	exit(code);
}
