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
#include "exec.h"
#include "clean_and_error.h"

static void	update_here_doc(t_token_stream_node *node,
		t_command_node *command_node)
{
	command_node->is_here_doc = TRUE;
	command_node->here_doc = node->value;
	node->value = NULL;
}

static int	find_good_input(t_token_stream_node *redirections_stream,
		t_command_node *command_node)
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
			return_value = write_redirection_in_command_node(
					redirections_stream->value,
					&command_node->fd_infile, open_input);
			break ;
		}
		redirections_stream = redirections_stream->prev;
	}
	return (return_value);
}

static int	find_good_output(t_token_stream_node *redirections_stream,
		t_command_node *command_node)
{
	int	return_value;

	return_value = 0;
	while (redirections_stream != NULL)
	{
		if (is_the_searched_token(redirections_stream, T_OUTPUT_FILE) == TRUE)
		{
				return_value = write_redirection_in_command_node(
					redirections_stream->value,
					&command_node->fd_outfile, open_output);
			break ;
		}
		else if (is_the_searched_token(redirections_stream, T_APPEND) == TRUE)
		{
				return_value = write_redirection_in_command_node(
					redirections_stream->value,
					&command_node->fd_outfile, open_append);
			break ;
		}
		redirections_stream = redirections_stream->prev;
	}
	return (return_value);
}

static int	get_good_redir(t_token_stream_node *redirections,
		t_command_node *command_node)
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

	if (command_node->redirections == NULL)
	{
		return (0);
	}
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
