/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream_node_management.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:32:31 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/12 18:32:31 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "AST.h"

t_token_stream_node	*ft_token_stream_new(t_token_type type, void *value)
{
	t_token_stream_node	*node;

	node = malloc(sizeof (t_token_stream_node));
	if (node)
	{
		node->type = type;
		if (value != NULL)
		{
			node->value = ft_strdup(value);
		}
		node->prev = NULL;
		node->next = NULL;
	}
	if (node->value == NULL)
	{
		free(node);
		node = NULL;
	}
	return (node);
}

void	ft_token_stream_add_back(t_token_stream_node **token_stream,
	t_token_stream_node *new_node)
{
	t_token_stream_node	*stream_cpy;

	if (new_node == NULL || token_stream == NULL)
	{
		return ;
	}
	if (*token_stream == NULL)
	{
		*token_stream = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
		return ;
	}
	stream_cpy = *token_stream;
	while (stream_cpy->next != NULL)
	{
		stream_cpy = stream_cpy->next;
	}
	new_node->prev = stream_cpy;
	stream_cpy->next = new_node;
	new_node->next = NULL;
	return ;
}

void	climb_stream_to_origin(t_token_stream_node **token_stream)
{
	if (*token_stream == NULL)
	{
		return ;
	}
	while ((*token_stream)->prev != NULL)
	{
		*token_stream = (*token_stream)->prev;
	}
}
