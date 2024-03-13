/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:48:33 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/29 16:49:01 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "built_ins.h"

void	pre_exec_set_up(t_core *core, t_command_node *current_command,
		int (*set_up_routine)(t_command_node *node))
{
	if (set_up_routine(current_command) == -1)
	{
		ft_clean_exit(core, 1);
	}
	return ;
}

void	build_and_exec_next_command(t_core *core,
		t_command_node *current_command)
{
	retrieve_path(core, current_command);
	execve(current_command->cmd[0], current_command->cmd, core->env);
	throw_error_message(current_command->cmd[0], execve_failure);
	ft_clean_exit(core, EXECVE_ERROR);
}

static void	exec_current_command(t_core *core, t_command_node *current_command,
		int built_in_index)
{
	t_built_ins	built_in_tab[7];
	int			built_in_return_value;

	init_built_ins_tab(built_in_tab);
	if (current_command->cmd == NULL)
	{
		return ;
	}
	else if (built_in_index == -1)
	{
		build_and_exec_next_command(core, current_command);
	}
	else
	{
		built_in_return_value = built_in_tab[built_in_index]
			(current_command->cmd, core);
		ft_clean_exit(core, built_in_return_value);
	}
}

void	child_routine(t_core *core, t_command_node *current_command,
		int built_in_index)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	safely_close_pipe_entry(current_command, READ_ENTRY);
	pre_exec_set_up(core, current_command, redirection_driver);
	pre_exec_set_up(core, current_command, manage_input);
	pre_exec_set_up(core, current_command, manage_output);
	exec_current_command(core, current_command, built_in_index);
	ft_clean_exit(core, 0);
}
