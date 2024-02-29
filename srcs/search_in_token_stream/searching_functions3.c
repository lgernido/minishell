/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_functions3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:32 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/19 15:21:33 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

t_bool	find_input_operator(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = find_infile_operator(token);
	if (return_value == FALSE)
	{
		return_value = find_here_doc_operator(token);
	}
	return (return_value);
}

t_bool	find_output_operator(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = find_outfile_operator(token);
	if (return_value == FALSE)
	{
		return_value = find_append_operator(token);
	}
	return (return_value);
}

t_bool	find_redirection_operator(t_token_stream_node *token)
{
	t_bool	return_value;

	return_value = find_input_operator(token);
	if (return_value == FALSE)
	{
		return_value = find_output_operator(token);
	}
	return (return_value);
}
