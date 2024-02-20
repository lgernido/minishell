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
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "built_ins.h"
#include "printerr.h"

void	get_inode_to_discard(ino_t *inode_tab, char *path1, char *path2)
{
	t_stat	stat[2];

	if (lstat(path1, &stat[0]) == -1)
	{
		perror("minishell");
		return ;
	}
	if (lstat(path2, &stat[1]) == -1)
	{
		perror("minishell");
		return ;
	}
	inode_tab[0] = stat[0].st_ino;
	inode_tab[1] = stat[1].st_ino;
	return ;
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
		perror("minishell");
	}
	return (return_value);
}

void	not_regular(void *arg)
{
	ft_printf_err("minishell: %s: not a regular file.\n", arg);
	return ;
}

void	is_dir(void *arg)
{
	ft_printf_err("minishell: %s: Is a directory.\n", arg);
	return ;
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
	if (stat->st_ino == inode_to_discard[0]
		|| stat->st_ino == inode_to_discard[1])
	{
		ft_del_node(&node);
		return (return_value);
	}
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

int	check_redirection_stream(t_token_stream_node *stream,
		ino_t *inode_to_discard)
{
	t_stat				stat_for_current_node;
	t_token_stream_node	*temp;
	int					return_value;

	return_value = 0;
	while (stream != NULL)
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
		if (return_value == -1)
		{
			break ;
		}
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
