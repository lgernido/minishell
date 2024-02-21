/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_stream_low_level_func.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:04 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/20 19:39:05 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"
#include "built_ins.h"
#include <asm-generic/errno-base.h>
#include <errno.h>

int	get_inode_to_discard(ino_t *inode_tab, char *path1, char *path2)
{
	t_stat	stat[2];

	if (lstat(path1, &stat[0]) == -1)
	{
		throw_error_message(path1, lstat_error);
		return (-1);
	}
	if (lstat(path2, &stat[1]) == -1)
	{
		throw_error_message(path2, lstat_error);
		return (-1);
	}
	inode_tab[0] = stat[0].st_ino;
	inode_tab[1] = stat[1].st_ino;
	return (0);
}

void	check_error_case(int *return_value, t_token_stream_node *node)
{
	if (is_the_searched_token(node, T_OUTPUT_FILE) == TRUE
		|| is_the_searched_token(node, T_APPEND) == TRUE)
	{
		if (errno == ENOENT)
		{
			*return_value = 1;
		}
		else
		{
			throw_error_message(node->value, lstat_error);
		}
	}
}

int	get_stat_for_current_node(t_token_stream_node *stream, t_stat *stat)
{
	int	return_value;

	return_value = 0;
	if (stream->type != T_HEREDOC)
	{
		return_value = lstat(stream->value, stat);
	}
	if (return_value == -1)
	{
		check_error_case(&return_value, stream);
	}
	return (return_value);
}

t_bool	check_for_redir_to_ignore(t_stat *stat, ino_t *inode_to_discard)
{
	int	return_value;

	return_value = FALSE;
	if (stat->st_ino == inode_to_discard[0]
		|| stat->st_ino == inode_to_discard[1])
	{
		return_value = TRUE;
	}
	return (return_value);
}

int	bad_redir(t_token_stream_node *node, t_stat *stat)
{
	int	return_value;

	return_value = 0;
	if (S_ISDIR(stat->st_mode) == TRUE)
	{
		throw_error_message(node->value, is_dir);
		return_value = -1;
	}
	else if (S_ISREG(stat->st_mode) != TRUE)
	{
		throw_error_message(node->value, not_regular);
		return_value = -1;
	}
	return (return_value);
}

int	check_for_bad_redirection(t_token_stream_node *node, t_stat *stat,
		ino_t *inode_to_discard)
{
	int	return_value;

	return_value = 0;
	if (node->type == T_HEREDOC)
	{
		return (return_value);
	}
	if (check_for_redir_to_ignore(stat, inode_to_discard) == TRUE)
	{
		ft_del_node(&node);
		return (return_value);
	}
	return_value = bad_redir(node, stat);
	return (return_value);
}
