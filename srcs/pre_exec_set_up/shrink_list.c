/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrink_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:44:38 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/19 17:44:39 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

static void	handle_nodes_to_shrink(t_token_stream_node **next_redirection)
{
	t_token_stream_node	*node_to_pop;

	free_if_needed(&(*next_redirection)->value);
	node_to_pop = (*next_redirection)->next;
	(*next_redirection)->value = node_to_pop->value;
	ft_extract_node(&node_to_pop);
	free(node_to_pop);
}

void	shrink_stream(t_token_stream_node **stream)
{
	t_token_stream_node	*next_redirection;

	next_redirection = find_searched_token(*stream, find_redirection_operator);
	while (next_redirection != NULL)
	{
		handle_nodes_to_shrink(&next_redirection);
		if (next_redirection->next == NULL)
		{
			break ;
		}
		*stream = next_redirection->next;
		next_redirection = find_searched_token(*stream,
				find_redirection_operator);
	}
	climb_stream_to_origin(stream);
}
