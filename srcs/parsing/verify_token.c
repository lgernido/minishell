/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifiy_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:53:17 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/26 10:53:18 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parenthesis_check(t_token_stream_node *token)
{
	int	return_value;

	return_value = 0;
	if (token->type == T_PAR_OPEN)
	{
		return_value = check_open_parenthesis(token);
	}
	else if (token->type == T_PAR_CLOSE)
	{
		return_value = check_close_parenthesis(token);
	}
	return (return_value);
}

int	ft_check_error(t_token_stream_node	*token)
{
	if ((token->type == T_PIPE || token->type == T_SEP || token->type == T_AND
			|| token->type == T_OR) && (!token->prev
			|| token->next->type == T_NEWLINE))
		return (1);
	if (token->type == T_REDIRECT && (token->prev
			&& token->prev->type == T_REDIRECT))
		return (1);
	if (token->type == T_NEWLINE && token->prev
		&& (token->prev->type == T_REDIRECT || token->prev->type == T_PIPE
			|| token->prev->type == T_AND || token->prev->type == T_OR))
		return (1);
	if ((token->type == T_PIPE || token->type == T_SEP || token->type == T_AND
			|| token->type == T_OR) && (token->prev->type == T_PIPE
			|| token->prev->type == T_SEP || token->prev->type == T_REDIRECT
			|| token->prev->type == T_AND || token->prev->type == T_OR))
		return (1);
	if ((token->type == T_REDIRECT && token->next->type == T_NEWLINE))
		return (1);
	return (0);
}
