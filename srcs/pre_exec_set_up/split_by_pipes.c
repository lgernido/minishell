/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:56:03 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/15 18:56:04 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "AST.h"

static size_t	retrieve_number_of_splitted_streams(
		t_token_stream_node *token_stream)
{
	int	number_of_pipes;

	number_of_pipes = 0;
	while (token_stream != NULL)
	{
		if (is_the_searched_token(token_stream, T_PIPE) == TRUE)
		{
			number_of_pipes += 1;
		}
		token_stream = token_stream->next;
	}
	return (number_of_pipes + 1);
}

static void	allocate_split_streams(t_token_stream_node ***split_streams,
		const size_t number_of_streams)
{
	*split_streams = ft_calloc(number_of_streams + 1,
			sizeof(t_token_stream_node *));
}

void	split_token_stream_by_pipes(t_ast_node *node)
{
	const size_t	number_of_splitted_streams
		= retrieve_number_of_splitted_streams(node->token_stream);

	node->number_of_split_streams = number_of_splitted_streams;
	allocate_split_streams(&(node->split_streams), number_of_splitted_streams);
	fill_stream(node, 0);
}
