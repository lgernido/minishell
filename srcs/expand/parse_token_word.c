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

static void	exit_properly(t_core *core, char *str_to_free)
{
	free(str_to_free);
	ft_clean_exit(core, MALLOC);
}

static int	extract_new_sub_token(t_core *core, char *token_string,
		char **to_dup_start, int *quote_flag)
{
	if (*to_dup_start != token_string
		&& (*quote_flag == -1 || *quote_flag == 0))
	{
		if (create_new_sub_token(core, *to_dup_start,
				token_string - 1, T_REGULAR) == -1)
		{
			return (-1);
		}
		*to_dup_start = token_string;
	}
	else if (*quote_flag == '\'' || *quote_flag == '"')
	{
		if (create_new_sub_token(core, *to_dup_start,
				token_string, *quote_flag) == -1)
		{
			return (-1);
		}
		*to_dup_start = token_string + 1;
	}
	update_current_quote(quote_flag, *token_string);
	return (0);
}

static void	extract_last_token(t_core *core, char *token_string,
		char *to_dup_start, int index)
{
	if (to_dup_start != token_string + index)
	{
		if (create_new_sub_token(core, to_dup_start,
				&token_string[index - 1], T_REGULAR) == -1)
		{
			exit_properly(core, token_string);
		}
	}
	free(token_string);
	return ;
}

void	parse_word_init(t_core *core, char *token_string)
{
	char	*to_dup_start;
	int		quote_flag;
	size_t	i;

	if (init_vector(core) == -1)
	{
		exit_properly(core, token_string);
	}
	to_dup_start = token_string;
	i = 0;
	quote_flag = -1;
	while (token_string[i] != '\0')
	{
		if (is_a_relevant_quote(token_string[i], quote_flag) == TRUE)
		{
			if (extract_new_sub_token(core, &token_string[i], &to_dup_start,
					&quote_flag) == -1)
			{
				exit_properly(core, token_string);
			}
		}
		++i;
	}
	extract_last_token(core, token_string, to_dup_start, i);
	return ;
}
