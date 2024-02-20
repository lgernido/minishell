/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_stream.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:30:23 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/19 19:30:24 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "AST.h"

void	discard_useless_redirections(t_token_stream_node *stream,
		t_bool (*compare_function)(char *node_value))
{
	t_token_stream_node	*node_to_delete;

	while (stream != NULL)
	{
		if (compare_function(stream->value) == TRUE)
		{
			node_to_delete = stream;
		}
		stream = stream->next;
	}
}

t_token_stream_node	*build_operator_stream(t_token_stream_node **stream,
		t_bool (*searching_function)(t_token_stream_node *token))
{
	const t_token_stream_node	*head = *stream;
	t_token_stream_node			*stream_to_return;
	t_token_stream_node			*node_to_pop;

	stream_to_return = NULL;
	node_to_pop = find_searched_token(*stream, searching_function);
	while (node_to_pop != NULL)
	{
		*stream = node_to_pop->next;
		ft_extract_node(&node_to_pop);
		ft_token_stream_add_back(&stream_to_return, node_to_pop);
		node_to_pop = find_searched_token(*stream, searching_function);
	}
	*stream = (t_token_stream_node *)head;
	return (stream_to_return);
}
