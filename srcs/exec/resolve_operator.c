/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:03:53 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/06 12:03:56 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"
#include "printerr.h"
#include "built_ins.h"
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void	lstat_error(void *arg)
{
	const int	errsv = errno;

	(void)arg;
	ft_printf_err("minishell: lstat: %s\n", strerror(errsv));
}

int	get_stat_for_the_path(const char *path_to_stat, ino_t *inode_to_fill)
{
	t_stat	stat_to_fill;
	int		return_value;

	return_value = lstat(path_to_stat, &stat_to_fill);
	if (return_value == 0)
	{
		*inode_to_fill = stat_to_fill.st_ino;
	}
	else
	{
		throw_error_message(NULL, lstat_error);
	}
	return (return_value);
}

int	init_inode_numbers(ino_t *inode, char *p1, char *p2)
{
	int	return_value;

	return_value = get_stat_for_the_path(p1, &inode[0]);
	if (return_value == 0)
	{
	return_value = get_stat_for_the_path(p2, &inode[1]);
	}
	return (return_value);
}

int	init_std_inode(ino_t std_inode[2][2])
{
	int	return_value;

	return_value = init_inode_numbers(std_inode[STDIN_NODE],
			STD_IN_DEV, STD_IN_PROC);
	if (return_value == 0)
	{
		return_value = init_inode_numbers(std_inode[STDOUT_NODE],
				STD_OUT_DEV, STD_OUT_PROC);
	}
	return (return_value);
}

int	check_if_stream_must_be_discard(t_token_stream_node **current_node, ino_t *relevant_inode)
{
	ino_t	redirection_inode;
	int		return_value;

	return_value = get_stat_for_the_path((*current_node)->value,
			&redirection_inode);
	if (return_value == 0)
	{
		if (redirection_inode == relevant_inode[0]
			|| redirection_inode == relevant_inode[1])
		{
			safely_del_node(current_node);
		}
		else
		{
			*current_node = (*current_node)->next;
		}
	}
	return (return_value);
}

int	discard_redirections_to_ignore(t_token_stream_node *redirections_stream)
{
	ino_t	inode_to_ignore[2][2];
	int		return_value;

	return_value = init_std_inode(inode_to_ignore);
	while (return_value == 0 && redirections_stream != NULL)
	{
		if (is_the_searched_token(redirections_stream, T_HEREDOC))
		{
			redirections_stream = redirections_stream->next;
		}
		else if (is_the_searched_token(redirections_stream, T_INPUT_FILE))
		{
			return_value = check_if_stream_must_be_discard(&redirections_stream,
					inode_to_ignore[STDIN_NODE]);
		}
		else
		{
			return_value = check_if_stream_must_be_discard(&redirections_stream,
					inode_to_ignore[STDOUT_NODE]);
		}
	}
	return (return_value);
}

void	open_file_error(void *arg)
{
	const int	errsv = errno;

	ft_printf_err("minishell: %s: %s\n", (char *)arg, strerror(errsv));
}

int	open_file(char *path, int flags)
{
	int	fd;

	fd = open(path, flags);
	if (fd == -1)
	{
		throw_error_message(path, open_file_error);
	}
	return (fd);
}

int	resolve_input(t_token_stream_node *redirections_stream)
{
	int	fd;

	if (is_the_searched_token(redirections_stream, T_INPUT_FILE))
	{
		fd = open_file(redirections_stream->value, O_RDONLY);
		if (fd != -1)
		{
			close (fd);
		}
	}
	else
	{
		fd = 0;
	}
	return (fd);
}

int	resolve_output(t_token_stream_node *redirections_stream)
{
	int	fd;

	if (is_the_searched_token(redirections_stream, T_OUTPUT_FILE))
	{
		fd = open_file(redirections_stream->value,
				O_WRONLY | O_CREAT | O_TRUNC);
	}
	else
	{
		fd = open_file(redirections_stream->value,
				O_WRONLY | O_CREAT | O_APPEND);
	}
	if (fd != -1)
	{
		close (fd);
	}
	return (fd);
}

int	verify_nodes(t_token_stream_node *redirections_stream)
{
	int	return_value;

	return_value = 0;
	while (redirections_stream != NULL && return_value != -1)
	{
		if (find_input_operator(redirections_stream) == TRUE)
		{
			return_value = resolve_input(redirections_stream);
		}
		else
		{
			return_value = resolve_output(redirections_stream);
		}
		redirections_stream = redirections_stream->next;
	}
	return (return_value);
}

void	get_down_stream(t_token_stream_node **stream)
{
	while ((*stream)->next != NULL)
	{
		*stream = (*stream)->next;
	}
	return ;
}

void	update_here_doc(t_token_stream_node *node, t_command_node *command_node)
{
	command_node->is_here_doc = TRUE;
	command_node->here_doc = node->value;
	node->value = NULL;
}

int	write_redirection(t_token_stream_node *redirections_stream, int *target_fd, int flags)
{
	int	return_value;
	int	fd;

	return_value = 0;
	fd = open_file(redirections_stream->value, flags);
	if (fd != -1)
	{
		*target_fd = fd;
	}
	else
	{
		return_value = -1;
	}
	return (return_value);
}

int	find_good_input(t_token_stream_node *redirections_stream, t_command_node *command_node)
{
	int	return_value;

	return_value = 0;
	while (redirections_stream != NULL)
	{
		if (is_the_searched_token(redirections_stream, T_HEREDOC) == TRUE)
		{
			update_here_doc(redirections_stream, command_node);	
			break ;
		}
		else if (is_the_searched_token(redirections_stream, T_INPUT_FILE)
			== TRUE)
		{
			return_value = write_redirection(redirections_stream,
					&command_node->fd_infile, O_RDONLY);
			break ;
		}
		redirections_stream = redirections_stream->prev;
	}
	return (return_value);
}

int	find_good_output(t_token_stream_node *redirections_stream, t_command_node *command_node)
{
	int	return_value;

	return_value = 0;
	while (redirections_stream != NULL)
	{
		if (is_the_searched_token(redirections_stream, T_OUTPUT_FILE) == TRUE)
		{
			return_value = write_redirection(redirections_stream,
					&command_node->fd_outfile, O_WRONLY | O_TRUNC);
			break ;
		}
		else if (is_the_searched_token(redirections_stream, T_REDIRECT) == TRUE)
		{
			return_value = write_redirection(redirections_stream,
					&command_node->fd_outfile, O_WRONLY | O_APPEND);
			break ;
		}
	}
	return (return_value);
}

int get_good_redir(t_token_stream_node *redirections, t_command_node *command_node)
{
	int	return_value;

	get_down_stream(&redirections);
	return_value = find_good_input(redirections, command_node);
	if (return_value != -1)
	{
	return_value = find_good_output(redirections, command_node);
	}
	return (return_value);
}

int	redirection_driver(t_command_node *command_node)
{
	int	return_value;

	return_value = verify_nodes(command_node->redirections);
	if (return_value != -1)
	{
		return_value = discard_redirections_to_ignore
			(command_node->redirections);
	}
	if (return_value != -1)
	{
		return_value = get_good_redir(command_node->redirections, command_node);
	}
	ft_token_stream_clear(&command_node->redirections);
	return (return_value);
}
