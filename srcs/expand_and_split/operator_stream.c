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
#include "built_ins.h"
#include <sys/types.h>

int	check_redirection_stream(t_token_stream_node *stream,
		ino_t *inode_to_discard)
{
	t_stat				stat_for_current_node;
	t_token_stream_node	*temp;
	int					return_value;

	return_value = 0;
	while (stream != NULL && return_value == 0)
	{
		return_value = get_stat_for_current_node(stream,
				&stat_for_current_node);
		if (return_value != -1)
		{
			temp = stream;
			stream = stream->next;
			return_value = check_for_bad_redirection(temp,
					&stat_for_current_node, inode_to_discard);
		}
	}
	return (return_value);
}

int	check_input(t_token_stream_node *input_stream)
{
	ino_t	inode_tab[2];
	int		return_value;

	return_value = get_inode_to_discard(inode_tab,
			"/dev/stdout", "/proc/self/fd/0");
	if (return_value != -1)
	{
		check_redirection_stream(input_stream, inode_tab);
	}
	return (return_value);
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

/* Go through stream
	 for each node , first del it if it points to sdtin/out
	 go error if notreg
	 open it
	 go error if no rights
	 close and del it if not last node
	 */
