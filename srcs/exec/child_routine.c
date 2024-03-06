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

void	safely_close_pipe_entry(t_command_node *node, int entry_to_close)
{
	if (node == NULL)
	{
		return ;
	}
	close_if_open(&node->pipe[entry_to_close]);
}

int	manage_here_doc(t_command_node *current_command)
{
	int	dest[2];
	int	return_value;

	return_value = pipe(dest);
	if (return_value == 0)
	{
		write(dest[WRITE_ENTRY], current_command->here_doc,
			ft_strlen(current_command->here_doc));
		close_if_open(&dest[WRITE_ENTRY]);
	}
	return_value = dup2(dest[READ_ENTRY], STDIN_FILENO);
	return (return_value);
}

int	manage_input(t_command_node *current_command)
{
	int	return_value;

	return_value = 0;
	if (current_command->fd_infile != -1)
	{
		return_value = dup2(current_command->fd_infile, STDIN_FILENO);
	}
	else if (current_command->is_here_doc == TRUE)
	{
		return_value = manage_here_doc(current_command);
	}
	else if (current_command->prev != NULL)
	{
		return_value = dup2(current_command->prev->pipe[READ_ENTRY],
				STDOUT_FILENO);
	}
	safely_close_pipe_entry(current_command->prev, READ_ENTRY);
	close_if_open(&current_command->fd_infile);
	return (return_value);
}

int	manage_output(t_command_node *current_command)
{
	int	return_value;

	return_value = 0;
	if (current_command->fd_outfile != -1)
	{
		return_value = dup2(current_command->fd_outfile, STDOUT_FILENO);
	}
	else if (current_command->next != NULL)
	{
		return_value = dup2(STDOUT_FILENO, current_command->pipe[WRITE_ENTRY]);
	}
	close_if_open(&current_command->pipe[WRITE_ENTRY]);
	close_if_open(&current_command->fd_outfile);
	return (return_value);
}

void	child_routine(t_core *core, t_command_node *current_command)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	safely_close_pipe_entry(current_command, READ_ENTRY);
	if (manage_input(current_command) == -1)
	{
		ft_clean_exit(core, errno);
	}
	if (manage_output(current_command) == -1)
	{
		ft_clean_exit(core, errno);
	}
	retrieve_path(core, current_command);
	execve(current_command->cmd[0], current_command->cmd, core->env);
	throw_exec_message(current_command->cmd[0]);
	ft_clean_exit(core, EXECVE_ERROR);
}
