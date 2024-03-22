/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:59:27 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/28 17:59:27 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	pipe_if_needed(t_command_node *current_command)
{
	int				return_value;

	return_value = 0;
	if (current_command->next != NULL)
	{
		return_value = checked_pipe(current_command->pipe);
	}
	return (return_value);
}

static pid_t	exec_command(t_core *core, t_command_node *current_command,
		int built_in_index)
{
	pid_t	pid;

	if (pipe_if_needed(current_command) == -1)
	{
		ft_clean_exit(core, errno);
	}
	pid = checked_fork();
	if (pid == -1)
	{
		ft_clean_exit(core, errno);
	}
	if (pid == 0)
	{
		child_routine(core, current_command, built_in_index);
	}
	else
	{
		parent_routine(current_command);
	}
	return (pid);
}

void	exec_init(t_core *core, t_command_node *command_list_head)
{
	pid_t			last_pid;
	int				command_index;

	while (core->ast->command_list != NULL)
	{
		command_index = is_built_in(core->ast->command_list->cmd[0]);
		check_errno(core);
		last_pid = exec_command(core, core->ast->command_list, command_index);
		core->ast->command_list = core->ast->command_list->next;
	}
	wait_for_childrens(core, last_pid);
	core->ast->command_list = command_list_head;
	choose_next_path_to_take(core);
	return ;
}
