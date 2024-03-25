/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_n_out_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:24:26 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/07 16:24:27 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "clean_and_error.h"

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

	return_value = checked_pipe(dest);
	if (return_value == 0)
	{
		write(dest[WRITE_ENTRY], current_command->here_doc,
			ft_strlen(current_command->here_doc));
		free(current_command->here_doc);
		close_if_open(&dest[WRITE_ENTRY]);
		return_value = checked_dup2(dest[READ_ENTRY], STDIN_FILENO);
		close_if_open(&dest[READ_ENTRY]);
	}
	return (return_value);
}

int	manage_input(t_command_node *current_command)
{
	int	return_value;

	return_value = 0;
	if (current_command->fd_infile != -1)
	{
		return_value = checked_dup2(current_command->fd_infile, STDIN_FILENO);
	}
	else if (current_command->is_here_doc == TRUE)
	{
		return_value = manage_here_doc(current_command);
	}
	else if (current_command->prev != NULL)
	{
		return_value = checked_dup2(current_command->prev->pipe[READ_ENTRY],
				STDIN_FILENO);
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
		return_value = checked_dup2(current_command->fd_outfile, STDOUT_FILENO);
	}
	else if (current_command->next != NULL)
	{
		return_value = checked_dup2(current_command->pipe[WRITE_ENTRY],
				STDOUT_FILENO);
	}
	close_if_open(&current_command->pipe[WRITE_ENTRY]);
	close_if_open(&current_command->fd_outfile);
	return (return_value);
}
