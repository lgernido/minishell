/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_functions2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:14:43 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/19 15:14:44 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

t_bool	find_infile_operator(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = FALSE;
	if (token->type == T_INPUT_FILE)
	{
		return_value = TRUE;
	}
	return (return_value);
}

t_bool	find_here_doc_operator(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = FALSE;
	if (token->type == T_HEREDOC)
	{
		return_value = TRUE;
	}
	return (return_value);
}

t_bool	find_outfile_operator(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = FALSE;
	if (token->type == T_OUTPUT_FILE)
	{
		return_value = TRUE;
	}
	return (return_value);
}

t_bool	find_append_operator(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = FALSE;
	if (token->type == T_APPEND)
	{
		return_value = TRUE;
	}
	return (return_value);
}
