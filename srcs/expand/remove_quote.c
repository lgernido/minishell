/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:26:50 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/19 13:26:52 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "expand.h"

static void	highlight_wildcards(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '*')
		{
			str[i] = -42;
		}
		++i;
	}
	return ;
}

static void	remove_quotes(t_core *core, t_sub_token *token_to_trim)
{
	const size_t	end_of_string_offset = ft_strlen(token_to_trim->value) - 2;
	char			*temp_str;

	temp_str = ft_strndup(token_to_trim->value + 1,
			token_to_trim->value + end_of_string_offset);
	if (temp_str == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	free(token_to_trim->value);
	token_to_trim->value = temp_str;
	return ;
}

void	remove_quotes_and_highlight_wildcards(t_core *core)
{
	size_t	i;

	i = 0;
	while (i < core->sub_token_vector->vector_size)
	{
		if (core->sub_token_vector->sub_token_list[i] != NULL)
		{
			if (core->sub_token_vector->sub_token_list[i]->value == T_REGULAR)
			{
				highlight_wildcards(core->sub_token_vector
					->sub_token_list[i]->value);
			}
			else
			{
				remove_quotes(core, core->sub_token_vector->sub_token_list[i]);
			}
		}
		++i;
	}
}
