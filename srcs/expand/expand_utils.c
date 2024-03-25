/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:40:39 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/19 16:40:41 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "expand.h"
#include <stdio.h>

t_bool	sub_token_need_expand(t_sub_token *sub_token)
{
	t_bool	return_value;

	return_value = TRUE;
	if (sub_token->type == T_SINGLE_QUOTES)
	{
		return_value = FALSE;
	}
	return (return_value);
}

void	expand_sub_token(t_core *core, int i)
{
	char	*expanded_token;
	char	*sub_token_value_copy;

	sub_token_value_copy = core->sub_token_vector
		->sub_token_list[i]->value;
	core->sub_token_vector->sub_token_list[i]->value = NULL;
	expanded_token = expand_var_init(core, sub_token_value_copy);
	if (expanded_token == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	core->sub_token_vector->sub_token_list[i]->value
		= expanded_token;
}

t_bool	is_valid_var_ender(char c)
{
	if (!(ft_isalnum(c) && c != '_') && c != '?')
	{
		return (TRUE);
	}
	return (FALSE);
}

char	*find_var_end(char *var_begin)
{
	while (is_valid_var_ender(*(var_begin)) == FALSE)
	{
		++var_begin;
	}
	return (var_begin);
}
