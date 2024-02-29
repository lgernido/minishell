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
#include <time.h>
#include <unistd.h>

t_bool	is_built_in(char *command)
{
	const char		**built_ins = (const char **)ft_split
		("env export unset cd pwd exit echo", ' ');
	const size_t	command_len = ft_strlen(command) + 1;
	int				i;

	i = 0;
	if (built_ins == NULL)
	{	
		return (FALSE);
	}
	while (built_ins[i] != NULL)
	{
		if (ft_strncmp(command, built_ins[i], command_len) == 0)
		{
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	is_pipe_needed(t_command_node *current_command)
{
	t_bool	return_value;

	return_value = FALSE;
	if (current_command->next != NULL)
	{
		return_value = TRUE;
	}
	return (return_value);
}

int	pipe_if_needed(t_command_node *current_command)
{
	const t_bool	need_pipe = is_pipe_needed(current_command);
	int				return_value;

	return_value = 0;
	if (current_command->next !=)
	{
		return_value = pipe(current_command->pipe);
	}
	return (return_value);
}

void	close_if_open(int *fd)
{
	if (*fd != -1)
	{
		close (*fd);
		*fd = -1;
	}
	return ;
}

void	parent_routine(t_command_node *current_command)
{
	close_if_open(&current_command->fd_infile);
	close_if_open(&current_command->fd_outfile);
	close_if_open(&current_command->pipe[WRITE_ENTRY]);
	safely_close_pipe_entry(current_command->prev, READ_ENTRY);
	return ;
}

void	exec_command(t_core *core, t_command_node *current_command)
{
	pid_t	pid;

	if (pipe_if_needed(current_command) == -1)
	{
		ft_clean_exit(core, PIPE_ERROR);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_clean_exit(core, FORK_ERROR);
	}
	if (pid == 0)
	{
		//
	}
	parent_routine(current_command);
	return ;
}

void	exec_init(t_core *core)
{
	while (core->ast->command_list != NULL)
	{
		if (is_built_in(core->ast->command_list->cmd[0]) == TRUE)
		{
			//
		}
		else
		{
			check_errno(core);
			// do other thing
		}
		core->ast->command_list = core->ast->command_list->next;
	}
}
