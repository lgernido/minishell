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
#include <signal.h>
#include <unistd.h>

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
	throw_error_message(current_command->cmd[0], exec_error);
	ft_clean_exit(core, EXECVE_ERROR);
}

void	child_routine(t_core *core, t_command_node *current_command)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	safely_close_pipe_entry(current_command, READ_ENTRY);
	pre_exec_set_up(core, current_command, redirection_driver);
	pre_exec_set_up(core, current_command, manage_input);
	pre_exec_set_up(core, current_command, manage_output);
	if (current_command->cmd != NULL)
	{
		build_and_exec_next_command(core, current_command);
	}
	ft_clean_exit(core, 0);
}
