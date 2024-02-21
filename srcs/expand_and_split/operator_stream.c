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
#include <asm-generic/errno-base.h>
#include <sys/stat.h>
#include <sys/types.h>

static void	discard_here_doc(t_token_stream_node **token)
{
	if (is_the_searched_token(*token, T_HEREDOC) == TRUE)
	{
		*token = (*token)->next;
	}
	return ;
}

int	check_input_redirection_stream(t_token_stream_node *stream,
		ino_t *inode_to_discard)
{
	t_stat				stat_for_current_node;
	int					return_value;

	ft_bzero(&stat_for_current_node, sizeof(t_stat));
	return_value = 0;
	while (stream != NULL && return_value != -1)
	{
		discard_here_doc(&stream);
		return_value = get_stat_for_the_path(&stat_for_current_node, stream);
		if (return_value != -1)
		{
			check_inode_to_discard(&stream, &stat_for_current_node,
				inode_to_discard);
		}
		else
		{
			throw_error_message(stream->value, lstat_error);
		}
		update_stream_if_needed(&stream);
	}
	return (return_value);
}

int	check_output_redirection_stream(t_token_stream_node *stream,
		ino_t *inode_to_discard)
{
	t_stat				stat_for_current_node;
	int					return_value;

	ft_bzero(&stat_for_current_node, sizeof(t_stat));
	return_value = 0;
	while (stream != NULL)
	{
		return_value = get_stat_for_the_path(&stat_for_current_node, stream);
		if (return_value != -1)
		{
			check_inode_to_discard(&stream, &stat_for_current_node,
				inode_to_discard);
		}
		else if (errno != ENOENT)
		{
			throw_error_message(stream->value, lstat_error);
		}
		update_stream_if_needed(&stream);
	}
	return (return_value);
}

int	check_input(t_token_stream_node *input_stream)
{
	ino_t	inode_tab[2];
	int		return_value;

	return_value = get_inode_to_discard(inode_tab, STD_IN_DEV, STD_IN_PROC);
	if (return_value != -1)
	{
		check_input_redirection_stream(input_stream, inode_tab);
	}
	return (return_value);
}

int	check_output(t_token_stream_node *input_stream)
{
	ino_t	inode_tab[2];
	int		return_value;

	return_value = get_inode_to_discard(inode_tab, STD_OUT_DEV, STD_OUT_PROC);
	if (return_value != -1)
	{
		check_output_redirection_stream(input_stream, inode_tab);
	}
	return (return_value);
}

t_token_stream_node	*build_operator_stream(t_token_stream_node *stream,
		t_bool (*searching_function)(t_token_stream_node *token))
{
	t_token_stream_node			*stream_to_return;
	t_token_stream_node			*node_to_pop;

	stream_to_return = NULL;
	node_to_pop = find_searched_token(stream, searching_function);
	while (node_to_pop != NULL)
	{
		stream = node_to_pop->next;
		ft_extract_node(&node_to_pop);
		ft_token_stream_add_back(&stream_to_return, node_to_pop);
		node_to_pop = find_searched_token(stream, searching_function);
	}
	return (stream_to_return);
}
