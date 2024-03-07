/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_verfication.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:42 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/07 11:19:44 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"
#include "exec.h"

static int	resolve_input(t_token_stream_node *redirections_stream)
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

static int	resolve_output(t_token_stream_node *redirections_stream)
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
