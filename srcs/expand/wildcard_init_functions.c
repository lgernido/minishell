/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_init_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:33:55 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 17:33:56 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"
#include "expand.h"
#include "clean_and_error.h"

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

int	init_wildcards_info(t_wildcard_info *wildcards_info,
		char *wildcard_string, DIR	*dir_ptr)
{
	int	return_value;

	return_value = 0;
	wildcards_info->last_char_is_a_wildcard
		= is_last_char_a_wildcard(wildcard_string);
	wildcards_info->first_char_is_a_wildcard
		= is_a_wildcard(wildcard_string[0]);
	wildcards_info->token_stream = NULL;
	wildcards_info->wildcard_tab = ft_split(wildcard_string, -42);
	wildcards_info->dir_ptr = dir_ptr;
	if (wildcards_info->wildcard_tab == NULL)
	{
		return_value = -1;
	}
	return (return_value);
}
