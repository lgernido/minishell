/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:25:52 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/15 14:25:53 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

static void	extract_new_sub_token(t_core *core, char *token_string,
		char **to_dup_start, int *quote_flag)
{
	if (*to_dup_start != token_string
		&& (*quote_flag == -1 || *quote_flag == 0))
	{
		create_new_sub_token(core,
			*to_dup_start, token_string - 1, T_REGULAR);
		*to_dup_start = token_string;
	}
	else if (*quote_flag == '\'' || *quote_flag == '"')
	{
		create_new_sub_token(core, *to_dup_start,
			token_string, *quote_flag);
		*to_dup_start = token_string + 1;
	}
	update_current_quote(quote_flag, *token_string);
}

void	parse_word_init(t_core *core, char *token_string)
{
	char	*to_dup_start;
	int		quote_flag;
	size_t	i;

	init_vector(core);
	to_dup_start = token_string;
	i = 0;
	quote_flag = -1;
	while (token_string[i] != '\0')
	{
		if (is_a_relevant_quote(token_string[i], quote_flag) == TRUE)
		{
			extract_new_sub_token(core, &token_string[i], &to_dup_start,
				&quote_flag);
		}
		++i;
	}
	if (to_dup_start != token_string + i)
	{
		create_new_sub_token(core,
			to_dup_start, &token_string[i - 1], T_REGULAR);
	}
	return ;
}
