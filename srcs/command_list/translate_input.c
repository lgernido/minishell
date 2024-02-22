/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:31:18 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/22 19:31:18 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "built_ins.h"
#include "minishell.h"

void	handle_here_doc(t_token_stream_node **input_stream,
		t_command_node *command_node)
{
	if ((*input_stream)->next != NULL)
	{
		*input_stream = (*input_stream)->next;
		ft_free_node(&(*input_stream)->prev);
	}
	else
	{
		command_node->is_here_doc = TRUE;
		// TODO : Expand here_doc if needed;
		command_node->here_doc = (*input_stream)->value;
		(*input_stream)->value = NULL;
		ft_free_node(input_stream);
	}
	return ;
}

int	handle_infiles(t_token_stream_node **input_stream,
		t_command_node *command_node)
{
	int	fd;
	int	return_value;

	fd = open((*input_stream)->value, O_RDONLY);
	return_value = 0;
	if (fd == -1)
	{
		return_value = -1;
		throw_error_message((*input_stream)->value, lstat_error);
	}
	else if ((*input_stream)->next != NULL)
	{
		close(fd);
		*input_stream = (*input_stream)->next;
		ft_free_node(&(*input_stream)->prev);
	}
	else
	{
		command_node->fd_infile = fd;
		ft_free_node(input_stream);
	}
	return (return_value);
}

int	translate_input(t_token_stream_node **input_stream,
		t_command_node *command_node)
{
	int	return_value;

	return_value = 0;
	if (input_stream == 0)
	{
		return (return_value);
	}
	while (*input_stream != NULL && return_value != -1)
	{
		if (is_the_searched_token(*input_stream, T_HEREDOC))
		{
			handle_here_doc(input_stream, command_node);
		}
		else
		{
			return_value = handle_infiles(input_stream, command_node);
		}
	}
	return (return_value);
}
