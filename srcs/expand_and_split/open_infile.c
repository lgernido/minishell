/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:01:22 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/20 20:01:23 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"

int	open_infiles(t_token_stream_node *input_stream, t_command_node *command_node)
{
	int	return_value;
	
	return_value = 0;
	while (input_stream != NULL)
	{
		if (input_stream->type == T_INPUT_FILE)
		{
			command_node->fd_infile = open(input_stream->value, O_RDONLY);
		}
	}
}
