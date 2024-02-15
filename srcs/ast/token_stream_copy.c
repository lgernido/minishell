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

void	ft_lst_cpy(t_token_stream_node *src,
	t_token_stream_node **dest, t_token_stream_node *limit)
{
	t_token_stream_node	*node;

	while (src != limit)
	{
		node = ft_token_stream_new(src->type, src->value);
		if (node == NULL)
		{
			ft_token_stream_clear(dest);
			errno = ENOMEM;
			return ;
		}
		ft_token_stream_add_back(dest, node);
		src = src->next;
	}
	return ;
}
