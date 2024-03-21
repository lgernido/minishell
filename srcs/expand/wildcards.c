/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:32:29 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/20 13:32:30 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

static t_bool	parse_dir_entry(t_wildcard_info *wildcard_info)
{
	size_t	i;
	t_bool	entry_still_match_wildcards;
	char	*tmp;

	tmp = wildcard_info->entry_to_parse;
	entry_still_match_wildcards = TRUE;
	i = 0;
	while (wildcard_info->wildcard_tab[i] != NULL
		&& entry_still_match_wildcards == TRUE)
	{
		entry_still_match_wildcards = match_wildcard_entry(
				&tmp, wildcard_info->wildcard_tab[i]);
		++i;
	}
	if (entry_still_match_wildcards == TRUE
		&& need_to_check_end_of_string(tmp, wildcard_info) == TRUE)
	{
		entry_still_match_wildcards = check_end_of_string(wildcard_info
				->entry_to_parse, wildcard_info->wildcard_tab[i - 1]);
	}
	return (entry_still_match_wildcards);
}

static void	check_dir_entry(t_core *core, t_wildcard_info *info)
{
	t_bool	entry_still_match;

	entry_still_match = TRUE;
	if (info->first_char_is_a_wildcard == FALSE)
	{
		entry_still_match = check_beginning_of_string(info->entry_to_parse,
				info->wildcard_tab[0]);
	}
	if (entry_still_match == TRUE)
	{
		entry_still_match = parse_dir_entry(info);
	}
	if (entry_still_match == TRUE)
	{
		save_dir_entry(core, info);
	}
	return ;
}

static t_token_stream_node	*get_wildcards(t_core *core, DIR *dir_ptr,
		char *wildcard_string)
{
	t_wildcard_info		wildcard_info;
	struct dirent		*dir_entry;
	t_token_stream_node	*stream_to_return;

	if (init_wildcards_info(&wildcard_info, wildcard_string, dir_ptr) == -1)
	{
		closedir(dir_ptr);
		ft_clean_exit(core, MALLOC);
	}
	dir_entry = NULL;
	while (1)
	{
		dir_entry = readdir(dir_ptr);
		if (dir_entry == NULL)
		{
			break ;
		}
		wildcard_info.entry_to_parse = dir_entry->d_name;
		check_dir_entry(core, &wildcard_info);
	}
	stream_to_return = wildcard_info.token_stream;
	wildcard_info.token_stream = NULL;
	clean_wildcard_info(&wildcard_info);
	return (stream_to_return);
}

int	wildcards_init(t_core *core, t_token_stream_node **current_token)
{
	const DIR			*dir_ptr = open_dir(core);
	t_token_stream_node	*entries_stream;
	const t_bool		prev_node_is_a_redir
		= is_prev_node_is_a_redirection(*current_token);
	int					return_value;

	entries_stream = get_wildcards(core, (DIR *)dir_ptr,
			(*current_token)->value);
	return_value = insert_entries_in_stream(current_token,
			&entries_stream, prev_node_is_a_redir);
	ft_clear_token_stream_if_needed(&entries_stream);
	return (return_value);
}
