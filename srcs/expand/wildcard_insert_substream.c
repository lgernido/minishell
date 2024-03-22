/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_insert_substream.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:36:24 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 17:36:25 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "clean_and_error.h"

static void	insert_dir_entries(t_token_stream_node **current_token,
		t_token_stream_node *dir_entries)
{
	t_token_stream_node	*prev_token;
	t_token_stream_node	*next_token;

	prev_token = (*current_token)->prev;
	next_token = (*current_token)->next;
	ft_free_node(current_token);
	dir_entries->prev = (t_token_stream_node *)prev_token;
	if (prev_token != NULL)
	{
		prev_token->next = dir_entries;
	}
	while (dir_entries->next != NULL)
	{
		dir_entries = dir_entries->next;
	}
	dir_entries->next = next_token;
	if (next_token != NULL)
	{
		next_token->prev = dir_entries;
	}
	*current_token = dir_entries;
	return ;
}

static int	manage_multiple_wildcards_match(t_token_stream_node **current_token,
		t_token_stream_node **entries_stream,
		const t_bool is_prev_node_a_redir)
{
	int	return_value;

	if (is_prev_node_a_redir == TRUE)
	{
		remove_highlighted_wildcards((*current_token)->value);
		throw_error_message((*current_token)->value, ambiguous_redir);
		return_value = -1;
	}
	else
	{
		insert_dir_entries(current_token, *entries_stream);
		*entries_stream = NULL;
		return_value = 0;
	}
	return (return_value);
}

int	insert_entries_in_stream(t_token_stream_node **current_token,
		t_token_stream_node **entries_stream,
		const t_bool is_prev_node_a_redir)
{
	const size_t	entries_stream_size = ft_token_stream_size(*entries_stream);
	int				return_value;

	return_value = 0;
	if (entries_stream_size == 0)
	{
		remove_highlighted_wildcards((*current_token)->value);
	}
	else if (entries_stream_size == 1)
	{
		free((*current_token)->value);
		(*current_token)->value = (*entries_stream)->value;
		(*entries_stream)->value = NULL;
	}
	else
	{
		return_value = manage_multiple_wildcards_match(current_token,
				entries_stream, is_prev_node_a_redir);
	}
	return (return_value);
}
