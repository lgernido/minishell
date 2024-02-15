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

void	clear_stream_and_exit(t_core *core,
		t_token_stream_node *stream, int code)
{
	ft_token_stream_clear(&stream);
	ft_clean_exit(core, code);
}
