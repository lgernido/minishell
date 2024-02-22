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

int	get_stat_for_the_path(t_stat *stat, t_token_stream_node *node)
{
	int	return_value;

	if (node == NULL)
	{
		return (0);
	}
	return_value = lstat(node->value, stat);
	return (return_value);
}

void	safely_del_node(t_token_stream_node **node)
{
	t_token_stream_node	*temp;

	temp = *node;
	*node = (*node)->next;
	ft_del_node(&temp);
}

int	check_inode_to_discard(t_token_stream_node **node, t_token_stream_node **stream, t_stat *stat,
		ino_t *inode_to_discard)
{
	int	return_value;

	return_value = 0;
	if (node == NULL)
	{
		return (return_value);
	}
	if (stat->st_ino == inode_to_discard[0]
		|| stat->st_ino == inode_to_discard[1])
	{
		if (*node == *stream)
		{
			*stream = (*stream)->next;
		}
		safely_del_node(node);
		++return_value;
	}
	return (return_value);
}

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
