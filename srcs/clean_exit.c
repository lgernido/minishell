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

#include "AST.h"
#include "minishell.h"

void	ft_clean_node(t_command_node *node)
{
	if (node->fd_infile != -1)
		close(node->fd_infile);
	if (node->fd_outfile != -1)
		close(node->fd_outfile);
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

void	ft_free_node(t_token_stream_node **node)
{
	if (*node == NULL)
		return ;
	if ((*node)->value)
	{
		free((*node)->value);
	}
	free(*node);
	*node = NULL;
}

void	ft_clear_token_stream_if_needed(t_token_stream_node **token_stream)
{
	if (*token_stream != NULL)
	{
		ft_token_stream_clear(token_stream);
	}
}

void	ft_token_stream_clear(t_token_stream_node **token_stream)
{
	t_token_stream_node	*tmp;

	climb_stream_to_origin(token_stream);
	while (*token_stream != NULL)
	{
		tmp = (*token_stream)->next;
		ft_free_node(token_stream);
		*token_stream = tmp;
	}
	*token_stream = NULL;
}

void	ft_split_stream_clean(t_token_stream_node ***split_streams, const size_t number_of_stream)
{
	t_token_stream_node **tmp;
	size_t	i;

	i = 0;
	tmp = *split_streams;
	while (i < number_of_stream)
	{
		ft_token_stream_clear(&(tmp[i]));
		i++;
	}
	free(tmp);
	tmp = NULL;
	*split_streams = tmp;
}

void	ft_ast_clear(t_ast_node **node)
{
	if (*node == NULL)
		return ;
	ft_ast_clear(&(*node)->on_success);
	ft_ast_clear(&(*node)->on_failure);
	if ((*node)->command_list != NULL)
	{
		while ((*node)->command_list->prev)
		{
			(*node)->command_list = (*node)->command_list->prev;
		}
		ft_command_clear(&(*node)->command_list);
	}
	if ((*node)->token_stream)
		ft_token_stream_clear(&(*node)->token_stream);
	if ((*node)->split_streams)
	{
		ft_split_stream_clean(&((*node)->split_streams),
			(*node)->number_of_split_streams);
	}
	free(*node);
	*node = NULL;
}

void	ft_clean_exit(t_core *core, int code)
{
	if (core->ast)
	{
		climb_tree_to_origin(&core->ast);
		ft_ast_clear(&core->ast);
	}
	if (core->env)
		ft_free_tab(core->env);
	// if (core->token_list)
	// 	ft_clear_token_list(&core->token_list, free);
	rl_clear_history();
	exit(code);
}
