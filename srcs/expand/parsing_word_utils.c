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

t_bool	is_valid_quote(char *quote_to_check)
{
	t_bool	return_value;

	return_value = TRUE;
	if (quote_to_check[0] == quote_to_check[1])
	{
		return_value = FALSE;
	}
	return (return_value);
}
