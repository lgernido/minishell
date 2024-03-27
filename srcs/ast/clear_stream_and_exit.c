/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_stream_and_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:52:08 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/13 19:52:08 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"
#include "clean_and_error.h"

void	clear_stream_and_exit(t_core *core,
		t_token_stream_node **stream, int code)
{
	ft_token_stream_clear(stream);
	ft_clean_exit(core, code);
}

void	check_for_error(t_core	*core, t_token_stream_node **first_token_stream,
		t_token_stream_node **second_token_stream)
{
	if (errno == ENOMEM)
	{
		ft_clear_token_stream_if_needed(first_token_stream);
		ft_clear_token_stream_if_needed(second_token_stream);
		ft_clean_exit(core, MALLOC);
	}
	return ;
}
