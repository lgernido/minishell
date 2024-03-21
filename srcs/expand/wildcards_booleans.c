/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:24:09 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 17:24:09 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_a_wildcard(char c)
{
	t_bool	return_value;

	return_value = FALSE;
	if (c == -42)
	{
		return_value = TRUE;
	}
	return (return_value);
}

t_bool	is_last_char_a_wildcard(char *str)
{
	const size_t	len = ft_strlen(str);

	return (is_a_wildcard(str[len - 1]));
}

t_bool	need_to_check_end_of_string(char *tmp_str,
		t_wildcard_info *wildcard_info)
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

t_bool	is_prev_node_is_a_redirection(t_token_stream_node *current_token)
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
