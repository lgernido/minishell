/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:30:24 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/29 17:30:25 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H

# include "minishell.h"

// Will close the specified entry of the pipe, after first verifying if	
// the node exist. Use to avoid segfaults.
void	safely_close_pipe_entry(t_command_node *node, int entry_to_close);

// Will search env for the path field, then send back, then
// write the good path directly into the command node
// In find_command_to_exec.c
void	retrieve_path(t_core *core, t_command_node *current_command);

// Entry point for the child process in child_routin.c
void	child_routine(t_core *core, t_command_node *current_command);

// Entry point for checking all the redirections and discard
// the ones that bash ignores (stdin/out).
int		discard_redirections_to_ignore(
			t_token_stream_node *redirections_stream);

// Will go through all node and manage redirection according to the
// token type. Stop and return -1 on error.
int		verify_nodes(t_token_stream_node *redirections_stream);

// ========================================================================= //

// Utils functions for redirections handling in redirection_handling_utils.c

// Will open the file with the specified flags, and return the fd on success.
// On error,  will print the error message according to errno value and
// return -1.
int		open_file(char *path, int flags);

// Will update the stream pointer to be the last node of the list.
// Mainly used here to select the last redirection as the used one.
void	get_down_stream(t_token_stream_node **stream);

// Will open the file specified by path, with the specified falgs.
// On succes, assigne the fd to the int pointer passed in argument
// and return .
// On error , will print the error message according to errno
// and return -1.
int		write_redirection_in_command_node(char *path,
			int *target_fd, int flags);

// ========================================================================= //

// Error message in exec_error_message.c
void	throw_exec_message(void *arg);

void	lstat_error(void *arg);

void	open_file_error(void *arg);

#endif
