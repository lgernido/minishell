/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:37:58 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 13:09:03 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"
#include "clean_and_error.h"

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
	{
		ft_token_stream_clear(&(*node)->token_stream);
	}
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
	if (core->token_list != NULL)
		ft_clear_token_list(&core->token_list);
}

void	ft_clean_exit(t_core *core, int code)
{
	if (core->env)
		ft_free_tab(core->env);
	clean_prev_command(core);
	rl_clear_history();
	exit(code);
}

void	exit_from_parsing(t_core *core, char *str, int error_code)
{
	free(str);
	ft_clean_exit(core, error_code);
}
