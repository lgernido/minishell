/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_and_wildcards_init.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:00:06 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 18:56:33 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include "expand.h"
#include "clean_and_error.h"

static void	expand_vector(t_core *core)
{
	size_t	i;

	i = 0;
	while (i < core->sub_token_vector->vector_size)
	{
		if (core->sub_token_vector->sub_token_list[i] != NULL)
		{
			if (sub_token_need_expand(core->sub_token_vector
					->sub_token_list[i]) == TRUE)
			{	
				expand_sub_token(core, i);
			}
		}
		++i;
	}
}

static char	*handle_word(t_core *core, char *token_value)
{
	char	*return_str;

	parse_word_init(core, token_value);
	expand_vector(core);
	return_str = join_vector_in_a_string(core);
	ft_clean_sub_vector(&core->sub_token_vector);
	return (return_str);
}

static int	need_wildcard_expand(t_core *core, t_token_stream_node **token)
{
	t_bool		return_value;
	const char	*token_value = (*token)->value;
	size_t		i;

	return_value = 0;
	i = 0;
	while (token_value[i] != '\0')
	{
		if (token_value[i] == -42)
		{
			return_value = wildcards_init(core, token);
			break ;
		}
		++i;
	}
	return (return_value);
}

int	expand_init(t_core *core, t_token_stream_node *token_stream)
{
	char						*token_value_copy;
	int							return_value;

	return_value = 0;
	while (token_stream != NULL && return_value == 0)
	{
		if (is_the_searched_token(token_stream, T_DOUBLE_QUOTES) == TRUE)
		{
			token_stream->value = expand_var_init(
					core, token_stream->value);
			check_errno(core);
		}
		else if (is_the_searched_token(token_stream, T_WORD) == TRUE)
		{
			remove_highlighted_char(token_stream->value, -38);
			token_value_copy = token_stream->value;
			token_stream->value = NULL;
			token_stream->value = handle_word(core, token_value_copy);
			return_value = need_wildcard_expand(core, &token_stream);
		}
		token_stream = token_stream->next;
	}
	return (return_value);
}
