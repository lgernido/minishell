/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:56:16 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/16 13:56:16 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include "clean_and_error.h"

static void	handle_prev_pointer(t_token_stream_node **node_to_pop)
{
	if ((*node_to_pop)->prev != NULL)
	{
		(*node_to_pop)->prev->next = (*node_to_pop)->next;
	}
	return ;
}

static void	handle_next_pointer(t_token_stream_node **node_to_pop)
{
	if ((*node_to_pop)->next != NULL)
	{
		(*node_to_pop)->next->prev = (*node_to_pop)->prev;
	}
	return ;
}

void	ft_extract_node(t_token_stream_node **node_to_pop)
{
	handle_prev_pointer(node_to_pop);
	handle_next_pointer(node_to_pop);
	return ;
}

void	ft_del_node(t_token_stream_node **node_to_del)
{
	ft_extract_node(node_to_del);
	ft_free_node(node_to_del);
}
