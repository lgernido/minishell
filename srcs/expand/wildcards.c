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

#include "libft.h"
#include "minishell.h"
#include "expand.h"
#include "AST.h"
#include "built_ins.h"
#include "printerr.h"
#include <dirent.h>

typedef struct s_wildcard_info
{
	char				**wildcard_tab;
	char				*entry_to_parse;
	t_bool				last_char_is_a_wildcard;
	DIR					*dir_ptr;
	t_token_stream_node	*token_stream;
}							t_wildcard_info;

void	opendir_error(void *arg)
{
	const int	errsv = errno;

	ft_printf_err("minishell: opendir: %s: %s\n", (char *)arg, strerror(errsv));
	errno = errsv;
}

DIR	*open_dir(t_core *core)
{
	DIR			*dir_ptr;
	const char	*cwd = get_pwd_in_buffer();

	if (cwd == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	dir_ptr = opendir(cwd);
	if (dir_ptr == NULL)
	{
		throw_error_message((char *)cwd, opendir_error);
		ft_clean_exit(core, MALLOC);
	}
	free((char *)cwd);
	if (dir_ptr == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	return (dir_ptr);
}

t_bool	is_last_char_a_wildcard(char *str)
{
	const size_t	len = ft_strlen(str);
	t_bool			return_value;

	return_value = FALSE;
	if (str[len - 1] == -42)
	{
		return_value = TRUE;
	}
	return (return_value);
}

int	init_wildcards_info(t_wildcard_info *wildcards_info,
		char *wildcard_string, DIR	*dir_ptr)
{
	int	return_value;

	return_value = 0;
	wildcards_info->last_char_is_a_wildcard
		= is_last_char_a_wildcard(wildcard_string);
	wildcards_info->token_stream = NULL;
	wildcards_info->wildcard_tab = ft_split(wildcard_string, -42);
	wildcards_info->dir_ptr = dir_ptr;
	if (wildcards_info->wildcard_tab == NULL)
	{
		return_value = -1;
	}
	return (return_value);
}

t_bool match_wildcard_entry(char **big, const char *little)
{
	const	size_t	little_len = ft_strlen(little);
	const	size_t	big_len = ft_strlen(*big);
	const	char	*little_location = ft_strnstr(*big, little, big_len);
	t_bool	return_value;

	if (little_location == NULL)
	{
		return_value = FALSE;
	}
	else
	{
		return_value = TRUE;
		*big = *big + little_len;
	}
	return (return_value);
}

t_bool	need_to_check_end_of_string(char *tmp_str, t_wildcard_info *wildcard_info)
{
	t_bool	return_value;

	return_value = FALSE;
	if (wildcard_info->last_char_is_a_wildcard == FALSE)
	{
		return_value = TRUE;
	}
	if (*tmp_str == '\0')
	{
		return_value = FALSE;
	}
	return (return_value);
}

t_bool	check_end_of_string(char *big, char *little)
{
	const size_t	big_len = ft_strlen(big);
	const size_t	little_len = ft_strlen(little);
	const char		*little_location = ft_strnstr(&big[big_len - little_len],
			little, little_len);
	t_bool			return_value;

	return_value = TRUE;
	if (little_location == NULL)
	{
		return_value = FALSE;
	}
	return (return_value);
}

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

void	parse_dir_entry(t_core *core, t_wildcard_info *wildcard_info)
{
	size_t	i;
	t_bool	entry_still_match_wildcards;
	char		*tmp;

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
	if (entry_still_match_wildcards == TRUE)
	{
		save_dir_entry(core, wildcard_info);
	}
	return ;
}

t_token_stream_node	*get_wildcards(t_core *core, DIR *dir_ptr,
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
		parse_dir_entry(core, &wildcard_info);
	}
	stream_to_return = wildcard_info.token_stream;
	wildcard_info.token_stream = NULL;
	clean_wildcard_info(&wildcard_info);
	return (stream_to_return);
}

t_bool is_prev_node_is_a_redirection(t_token_stream_node *current_token)
{
	t_bool	return_value;

	return_value = FALSE;
	if (current_token->prev != NULL)
	{
		if (current_token->prev->type == T_APPEND
			|| current_token->prev->type == T_INPUT_FILE
			|| current_token->type == T_OUTPUT_FILE)
		{
			return_value = TRUE;
		}
	}
	return (return_value);
}

size_t	ft_token_stream_size(t_token_stream_node *token_stream)
{
	size_t	size;

	size = 0;
	while (token_stream != NULL)
	{
		++size;
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
	}
	return ;
}

void	wildcards_init(t_core *core, t_token_stream_node *current_token)
{
	const DIR		*dir_ptr = open_dir(core);
	t_token_stream_node	*entries_stream;
	const t_bool	prev_node_is_a_redir
		= is_prev_node_is_a_redirection(current_token);
	size_t			entries_stream_size;

	entries_stream = get_wildcards(core, (DIR *)dir_ptr, current_token->value);
	entries_stream_size = ft_token_stream_size(entries_stream);
	if (entries_stream_size == 0)
	{
		remove_highlighted_wildcards(current_token->value);
	}
}
/*
	Pseudo :
		check if prev is a redir, store it in a flag
		Open_dir
		check if last char of str is -42, store it in a flag
		For each entries :
		while
		strnstr in with the case of the tab
		if return != NULL
		return to last_case
		if return == NULL
		return
		go end of substr
		go one more case
		next iter 
		aftr while
		if tab[i] == NULL && flag condition is match
		save this entrie of the dir
	 */
