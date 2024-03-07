/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:35:31 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/07 17:35:32 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	parent_routine(t_command_node *current_command)
{
	close_if_open(&current_command->fd_infile);
	close_if_open(&current_command->fd_outfile);
	close_if_open(&current_command->pipe[WRITE_ENTRY]);
	safely_close_pipe_entry(current_command->prev, READ_ENTRY);
	return ;
}

static int	wait_last_child(pid_t last_pid)
{
	int	status;
	int	return_value;

	waitpid(last_pid, &status, 0);
	if (WIFSIGNALED(status) == TRUE)
	{
		return_value = WTERMSIG(status);
	}
	else
	{
		return_value = WEXITSTATUS(status);
	}
	return (return_value);
}

void	wait_for_childrens(t_core *core, pid_t last_pid,
		t_bool last_cmd_is_a_built_in)
{
	if (last_cmd_is_a_built_in == FALSE)
	{
		core->error_code = wait_last_child(last_pid);
	}
	while (wait(NULL) != -1)
	{
	}
	return ;
}
