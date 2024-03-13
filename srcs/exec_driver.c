/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_driver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:51:24 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/07 17:51:25 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

static t_bool	is_a_pipeline(t_command_node *command_stream)
{
	t_bool	return_value;

	return_value = TRUE;
	if (command_stream == NULL || command_stream->next == NULL)
	{
		return_value = FALSE;
	}
	return (return_value);
}

static void	exec_single_command(t_core *core, t_command_node *head)
{
	int	built_in_index;

	built_in_index = is_built_in(core->ast->command_list->cmd[0]);
	check_errno(core);
	if (built_in_index == -1)
	{
		exec_init(core, head);
	}
	else
	{
		exec_built_ins(core, core->ast->command_list, built_in_index);
	}
}

void	exec_driver(t_core *core)
{
	t_command_node	*command_head;

	setup_exec_sig();
	climb_command_list_to_origin(&core->ast->command_list);
	command_head = core->ast->command_list;
	if (is_a_pipeline(core->ast->command_list) == TRUE)
	{
		exec_init(core, command_head);
	}
	else
	{
		exec_single_command(core, command_head);
	}
	return ;
}
