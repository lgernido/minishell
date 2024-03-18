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

void	expand_init(t_core *core, t_token_stream_node *token_stream)
{
	while (token_stream != NULL)
	{
		if (is_the_searched_token(token_stream, T_TO_EXPAND) == TRUE)
		{
			token_stream->value = expand_var_init(core, token_stream->value);
			check_errno(core);
		}
		else if (is_the_searched_token(token_stream, T_WORD) == TRUE)
		{
		}
		token_stream = token_stream->next;
	}
}
