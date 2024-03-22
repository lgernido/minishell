/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_word_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:46:52 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/15 17:46:52 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

t_bool	is_a_relevant_quote(int c, int flag)
{
	if (flag == 0 || flag == -1)
	{
		if (c == '"' || c == '\'')
		{
			return (TRUE);
		}
	}
	else
	{
		if (c == flag)
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

void	update_current_quote(int *current_quote, int quote)
{
	if ((*current_quote == 0 || *current_quote == -1)
		&& (quote == '\'' || quote == '"'))
	{
		*current_quote = quote;
	}
	else
	{
		*current_quote = 0;
	}
	return ;
}
