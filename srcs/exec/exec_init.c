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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int	is_built_in(char *command)
{
	const char		**built_ins = (const char **)ft_split
		("env export unset cd pwd exit echo", ' ');
	const size_t	command_len = ft_strlen(command) + 1;
	int				i;

	i = 0;
	if (built_ins == NULL)
	{	
		return (-1);
	}
	while (built_ins[i] != NULL)
	{
		if (ft_strncmp(command, built_ins[i], command_len) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	pipe_if_needed(t_command_node *current_command)
{
	int				return_value;

	return_value = 0;
	if (current_command->next != NULL)
	{
		return_value = checked_pipe(current_command->pipe);
	}
	return (return_value);
}

void	parent_routine(t_command_node *current_command)
{
	close_if_open(&current_command->fd_infile);
	close_if_open(&current_command->fd_outfile);
	close_if_open(&current_command->pipe[WRITE_ENTRY]);
	safely_close_pipe_entry(current_command->prev, READ_ENTRY);
	return ;
}

pid_t	exec_command(t_core *core, t_command_node *current_command)
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
		child_routine(core, current_command);
	}
	parent_routine(current_command);
	return (pid);
}

int	wait_last_child(pid_t last_pid)
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

void	exec_init(t_core *core)
{
	pid_t	last_pid;
	t_bool	last_cmd_is_a_build_in;

	while (core->ast->command_list != NULL)
	{
		if (is_built_in(core->ast->command_list->cmd[0]) == TRUE)
		{
			last_cmd_is_a_build_in = TRUE;
		}
		else
		{
			last_cmd_is_a_build_in = FALSE;
			check_errno(core);
			last_pid = exec_command(core, core->ast->command_list);
		}
		core->ast->command_list = core->ast->command_list->next;
	}
	wait_for_childrens(core, last_pid, last_cmd_is_a_build_in);
}
