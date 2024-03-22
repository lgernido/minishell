/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discard_standard_entries.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:05:29 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/07 11:05:30 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"
#include "exec.h"
#include "clean_and_error.h"

static int	get_stat_for_the_path(const char *path_to_stat,
		ino_t *inode_to_fill)
{
	t_stat	stat_to_fill;
	int		return_value;

	return_value = lstat(path_to_stat, &stat_to_fill);
	if (return_value == 0)
	{
		*inode_to_fill = stat_to_fill.st_ino;
	}
	else
	{
		throw_error_message("lstat", exec_error);
	}
	return (return_value);
}

static int	init_inode_numbers(ino_t *inode, char *p1, char *p2)
{
	int	return_value;

	return_value = get_stat_for_the_path(p1, &inode[0]);
	if (return_value == 0)
	{
	return_value = get_stat_for_the_path(p2, &inode[1]);
	}
	return (return_value);
}

static int	init_std_inode(ino_t std_inode[2][2])
{
	int	return_value;

	return_value = init_inode_numbers(std_inode[STDIN_NODE],
			STD_IN_DEV, STD_IN_PROC);
	if (return_value == 0)
	{
		return_value = init_inode_numbers(std_inode[STDOUT_NODE],
				STD_OUT_DEV, STD_OUT_PROC);
	}
	return (return_value);
}

static int	check_if_stream_must_be_discard(t_token_stream_node **current_node,
		ino_t *relevant_inode)
{
	ino_t	redirection_inode;
	int		return_value;

	return_value = get_stat_for_the_path((*current_node)->value,
			&redirection_inode);
	if (return_value == 0)
	{
		if (redirection_inode == relevant_inode[0]
			|| redirection_inode == relevant_inode[1])
		{
			safely_del_node(current_node);
		}
		else
		{
			*current_node = (*current_node)->next;
		}
	}
	return (return_value);
}

int	discard_redirections_to_ignore(t_token_stream_node *redirections_stream)
{
	ino_t	inode_to_ignore[2][2];
	int		return_value;

	return_value = init_std_inode(inode_to_ignore);
	while (return_value == 0 && redirections_stream != NULL)
	{
		if (is_the_searched_token(redirections_stream, T_HEREDOC))
		{
			redirections_stream = redirections_stream->next;
		}
		else if (is_the_searched_token(redirections_stream, T_INPUT_FILE))
		{
			return_value = check_if_stream_must_be_discard(&redirections_stream,
					inode_to_ignore[STDIN_NODE]);
		}
		else
		{
			return_value = check_if_stream_must_be_discard(&redirections_stream,
					inode_to_ignore[STDOUT_NODE]);
		}
	}
	return (return_value);
}
