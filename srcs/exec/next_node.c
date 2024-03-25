/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:55:01 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/08 14:55:02 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean_and_error.h"

void	setup_next_node(t_core *core, t_ast_node *path_to_take,
		t_ast_node *path_to_clear)
{
	ft_ast_clear(&path_to_clear);
	ft_ast_node_clear(&core->ast);
	core->ast = path_to_take;
	if (core->ast != NULL)
	{
		core->ast->parent = NULL;
	}
	return ;
}

void	choose_next_path_to_take(t_core *core)
{
	printf("Last exit code in node: %d\n", core->error_code);
	if (g_signal == 130)
	{
		ft_ast_clear(&core->ast);
	}
	else if (core->error_code == 0)
	{
		setup_next_node(core, core->ast->on_success, core->ast->on_failure);
	}
	else
	{
		setup_next_node(core, core->ast->on_failure, core->ast->on_success);
	}
	if (core->ast != NULL)
	{
		ast_driver(core);
	}
	return ;
}
