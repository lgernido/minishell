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

void	ft_split_stream_clean(t_ast_node *ast)
{
	t_token_stream_node **tmp;
	size_t	i;

	i = 0;
	tmp = ast->split_streams;
	while (i < ast->number_of_split_streams)
	{
		ft_token_stream_clear(&(tmp[i]));
		i++;
	}
	free(tmp);
	ast->split_streams = NULL;
}

void	ft_ast_node_clear(t_ast_node **node)
{
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
		ft_split_stream_clean(*node);
	}
	free(*node);
	*node = NULL;
}

void	ft_ast_clear(t_ast_node **node)
{
	if (*node == NULL)
		return ;
	ft_ast_clear(&(*node)->on_success);
	ft_ast_clear(&(*node)->on_failure);
	ft_ast_node_clear(node);
}

void	ft_clean_sub_token(t_sub_token **token)
{
	void	*str;

	str = (*token)->value;
	free_if_needed(&str);
	free(*token);
	token = NULL;
	return ;
}

void	ft_clean_sub_token_list(t_sub_token **token_list, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (token_list[i] != NULL)
		{
			ft_clean_sub_token(&token_list[i]);
		}
		++i;
	}
	free(token_list);
}

void	ft_clean_sub_vector(t_sub_token_vector **vector)
{
	ft_clean_sub_token_list((*vector)->sub_token_list, (*vector)->vector_size);
	(*vector)->sub_token_list = NULL;
	free(*vector);
	*vector = NULL;
}

void	clean_prev_command(t_core *core)
{
	if (core->ast)
	{
		climb_tree_to_origin(&core->ast);
		ft_ast_clear(&core->ast);
	}
	if (core->sub_token_vector)
	{
		ft_clean_sub_vector(&core->sub_token_vector);
	}
	// if (core->token_list)
	// 	ft_clear_token_list(&core->token_list, free);
}

void	ft_clean_exit(t_core *core, int code)
{
	if (core->env)
		ft_free_tab(core->env);
	clean_prev_command(core);
	rl_clear_history();
	exit(code);
}
