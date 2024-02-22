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
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int	verify_inputs(t_token_stream_node *node, t_stat *stat)
{
	const int	return_value = get_stat_for_the_path(stat, node);

	if (is_the_searched_token(node, T_HEREDOC))
	{
		return (0);
	}
	if (return_value == -1)
	{
		throw_error_message(node->value, lstat_error);
	}
	return (return_value);
}

int	verify_outputs(t_token_stream_node *node, t_stat *stat)
{
	int	return_value;

	return_value = 0;
	return_value = get_stat_for_the_path(stat, node);
	if (return_value == -1)
	{
		if (errno == ENOENT)
		{
			return_value = 0;
		}
		else
		{
			throw_error_message(node->value, lstat_error);
		}
	}
	return (return_value);
}

static int	check_input_redirection_stream(t_token_stream_node **stream,
		int (*verif_function)(t_token_stream_node *node, t_stat *stat),
		ino_t *inode_to_discard)
{
	t_stat				stat_for_current_node;
	t_token_stream_node *looked_node;
	int					return_value;

	ft_bzero(&stat_for_current_node, sizeof(t_stat));
	return_value = 0;
	looked_node = *stream;
	while (looked_node != NULL && return_value != -1)
	{
		return_value = verif_function(looked_node, &stat_for_current_node);
		if (check_inode_to_discard(&looked_node, stream, &stat_for_current_node,
				inode_to_discard) == 0)
		{
			update_stream_if_needed(&looked_node);
		}
		ft_bzero(&stat_for_current_node, sizeof(t_stat));
	}
	return (return_value);
}

int	check_redirections(t_token_stream_node **input_stream,
		int (*verif_function)(t_token_stream_node *node, t_stat *stat),
		char *path1, char *path2)
{
	ino_t	inode_tab[2];
	int		return_value;

	return_value = get_inode_to_discard(inode_tab, path1, path2);
	if (return_value != -1)
	{
		check_input_redirection_stream(input_stream, verif_function, inode_tab);
	}
	return (return_value);
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
