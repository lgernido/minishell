/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:04:38 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/22 20:04:38 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include "built_ins.h"

static	int	open_truncate(char *path)
{
	int	fd;

	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 00244 | 00400);
	if (fd == -1)
	{
		throw_error_message(path, lstat_error);
	}
	return (fd);
}

static	int	open_append(char *path)
{
	int	fd;

	fd = open(path, O_RDWR | O_CREAT | O_APPEND, 00244 | 00400);
	if (fd == -1)
	{
		throw_error_message(path, lstat_error);
	}
	return (fd);
}
static	int	handle_outfiles(t_token_stream_node **output_stream,
		t_command_node *command_node, int (*open_function)(char *path))
{
	int	fd;
	int	return_value;

	return_value = 0;
	fd = open_function((*output_stream)->value);
	if (fd == -1)
	{
		return_value = -1;
	}
	else if ((*output_stream)->next != NULL)
	{
		close(fd);
		*output_stream = (*output_stream)->next;
		ft_free_node(&(*output_stream)->prev);
	}
	else
	{
		command_node->fd_outfile = fd;
		ft_free_node(output_stream);
	}
	return (return_value);
}

int	translate_output(t_token_stream_node **output_stream,
		t_command_node *command_node)
{
	int	return_value;

	return_value = 0;
	if (output_stream == 0)
	{
		return (return_value);
	}
	while (*output_stream != NULL && return_value != -1)
	{
		if (is_the_searched_token(*output_stream, T_OUTPUT_FILE))
		{
			return_value = handle_outfiles(output_stream,
					command_node, open_truncate);
		}
		else
		{
			return_value = handle_outfiles(output_stream,
					command_node, open_append);
		}
	}
	return (return_value);
}
