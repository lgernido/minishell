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

#include "data_structures_define_and_includes.h"
#include "minishell.h"
#include "AST.h"
#include "clean_and_error.h"

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

void	remove_highlighted_char(char *str, int to_remove)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == to_remove)
		{
			str[i] *= -1;
		}
		++i;
	}
	return ;
}

t_bool	is_an_entry_to_parse(t_wildcard_info *info)
{
	if (info->entry_to_parse[0] != '.')
	{
		return (TRUE);
	}
	if (info->wildcard_tab[0][0] == '.'
		&& info->first_char_is_a_wildcard == FALSE)
	{
		return (TRUE);
	}
	return (FALSE);
}
