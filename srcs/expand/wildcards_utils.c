/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:30:00 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 17:30:01 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

void	clean_wildcard_info(t_wildcard_info *wildcard_info)
{
	ft_free_tab(wildcard_info->wildcard_tab);
	closedir(wildcard_info->dir_ptr);
	ft_clear_token_stream_if_needed(&wildcard_info->token_stream);
}

void	save_dir_entry(t_core	*core, t_wildcard_info *wildcard_info)
{
	t_token_stream_node	*new_node;

	new_node = ft_token_stream_new(T_WORD, wildcard_info->entry_to_parse);
	if (new_node == NULL)
	{
		clean_wildcard_info(wildcard_info);
		ft_clean_exit(core, MALLOC);
	}
	ft_token_stream_add_back(&wildcard_info->token_stream, new_node);
}

size_t	ft_token_stream_size(t_token_stream_node *token_stream)
{
	size_t	size;

	size = 0;
	while (token_stream != NULL)
	{
		++size;
		token_stream = token_stream->next;
	}
	return (size);
}

void	remove_highlighted_wildcards(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == -42)
		{
			str[i] = '*';
		}
		++i;
	}
	return ;
}
