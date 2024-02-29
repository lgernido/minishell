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
#include <unistd.h>

void	safely_close_pipe_entry(t_command_node *node, int entry_to_close)
{
	if (node == NULL)
	{
		return ;
	}
	close_if_open(&node->pipe[entry_to_close]);
}

int	manage_input(t_command_node *current_command)
{
	int	return_value;

	return_value = 0;
	if (current_command->fd_infile != -1)
	{
		return_value = dup2(current_command->fd_infile, STDIN_FILENO);
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
	safely_close_pipe_entry(current_command->next, READ_ENTRY);
	if (manage_input(current_command) == -1)
	{
		ft_clean_exit(core, errno);
	}
	if (manage_output(current_command) == -1)
	{
		ft_clean_exit(core, errno);
	}
}
