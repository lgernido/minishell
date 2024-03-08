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

#include "minishell.h"
#include "AST.h"

void	safely_del_node(t_token_stream_node **node)
{
	t_token_stream_node	*temp;

	temp = *node;
	*node = (*node)->next;
	ft_del_node(&temp);
}

t_token_stream_node	*build_operator_stream(t_token_stream_node **stream,
		t_bool (*searching_function)(t_token_stream_node *token))
{
	t_token_stream_node			*stream_to_return;
	t_token_stream_node			*node_to_pop;

	stream_to_return = NULL;
	node_to_pop = find_searched_token(*stream, searching_function);
	while (node_to_pop != NULL)
	{
		ft_lst_cpy(node_to_pop, &stream_to_return, node_to_pop->next);
		if (stream_to_return == NULL)
		{
			return (stream_to_return);
		}
		if (node_to_pop == *stream)
		{
			*stream = (*stream)->next;
		}
		safely_del_node(&node_to_pop);
		node_to_pop = find_searched_token(*stream, searching_function);
	}
	return (stream_to_return);
}
