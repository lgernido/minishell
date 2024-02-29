/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_split_stream_in_command_list.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:26:04 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/22 19:26:04 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	command_stream_size(t_token_stream_node *command_stream)
{
	size_t	counter;

	counter = 0;
	while (command_stream != NULL)
	{
		++counter;
		command_stream = command_stream->next;
	}
	return (counter);
}

void	build_command_from_tokens(t_token_stream_node *command_stream,
		t_command_node *command_node)
{
	const size_t		counter = command_stream_size(command_stream);
	size_t				i;

	i = 0;
	command_node->cmd = ft_calloc(counter + 1, sizeof(char *));
	if (command_node->cmd == NULL)
	{
		return ;
	}
	while (i < counter)
	{
		command_node->cmd[i] = command_stream->value;
		command_stream->value = NULL;
		command_stream = command_stream->next;
		++i;
	}
	return ;
}

int	build_command_node(t_token_stream_node **command_stream,
		t_token_stream_node **input_stream, t_token_stream_node **output_stream,
		t_command_node *command_node)
{
	int	return_value;

	return_value = 0;
	return_value = translate_input(input_stream, command_node);
	if (return_value == 0)
	{
		return_value = translate_output(output_stream, command_node);
	}
	if (return_value == 0)
	{
		build_command_from_tokens(*command_stream, command_node);
		if (command_node->cmd == NULL && errno == ENOMEM)
		{
			return_value = MALLOC;
		}
	}
	return (return_value);
}
