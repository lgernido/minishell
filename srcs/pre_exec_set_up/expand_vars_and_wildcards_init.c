/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:06:33 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/15 18:06:33 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include "expand.h"

void	expand_vector(t_core *core)
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

char	*handle_word(t_core *core, char *token_value)
{
	char	*return_str;

	return_str = get_rid_of_double_quote(token_value);
	check_for_mem_error(core, &return_str, &token_value);
	parse_word_init(core, token_value);
	expand_vector(core);
	return_str = join_vector_in_a_string(core);
	return (return_str);
}

void	expand_init(t_core *core, t_token_stream_node *token_stream)
{
	char	*token_value_copy;

	while (token_stream != NULL)
	{
		if (is_the_searched_token(token_stream, T_TO_EXPAND) == TRUE)
		{
			token_stream->value = expand_var_init(core, token_stream->value);
			check_errno(core);
		}
		else if (is_the_searched_token(token_stream, T_WORD) == TRUE)
		{
			token_value_copy = token_stream->value;
			token_stream->value = NULL;
			token_stream->value = handle_word(core, token_value_copy);
		}
		token_stream = token_stream->next;
	}
}
