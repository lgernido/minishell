/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_split_streams.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:11:25 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/15 19:11:27 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"

void	pop_last_node(t_token_stream_node **token_stream)
{
	t_token_stream_node	*tmp_node;

	if (*token_stream != NULL)
	{
		tmp_node = *token_stream;
		*token_stream = (*token_stream)->next;
		ft_del_node(&tmp_node);
	}
	return ;
}

static void	clear_stream_till_limit(t_token_stream_node **token_stream,
		t_token_stream_node *limit)
{
	t_token_stream_node	*tmp_node;

	while (*token_stream != limit)
	{
		tmp_node = *token_stream;
		*token_stream = (*token_stream)->next;
		ft_del_node(&tmp_node);
	}
	pop_last_node(token_stream);
}

static void	fill_next_stream_if_needed(t_ast_node *node,
		const size_t index_in_split_streams)
{
	if (node->token_stream == NULL || errno == ENOMEM)
	{
		return ;
	}
	fill_stream(node, index_in_split_streams + 1);
}

void	fill_stream(t_ast_node *node, const size_t index_in_split_streams)
{
	t_token_stream_node	*next_pipe;

	if (node->token_stream == NULL)
	{
		return ;
	}
	next_pipe = find_searched_token(node->token_stream, find_pipe);
	ft_lst_cpy(node->token_stream, &node->split_streams[index_in_split_streams],
		next_pipe);
	clear_stream_till_limit(&(node->token_stream), next_pipe);
	fill_next_stream_if_needed(node, index_in_split_streams);
}
