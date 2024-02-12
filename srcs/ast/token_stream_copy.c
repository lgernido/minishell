/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream_copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:25:47 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/12 18:25:48 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

void	ft_lst_cpy(t_core	*core, t_token_stream_node *token_stream,
	t_token_stream_node *limit)
{
	t_token_stream_node	*local_node_token_stream;
	t_token_stream_node	*node;

	local_node_token_stream = core->ast->token_stream;
	while (token_stream != limit)
	{
		node = ft_token_stream_new(token_stream->type, token_stream->value);
		if (node == NULL)
			ft_clean_exit(core, MALLOC);
		ft_token_stream_add_back(&local_node_token_stream, node);
	}
}
