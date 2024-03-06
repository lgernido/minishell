/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_stream_low_level_func.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:04 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/20 19:39:05 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"
#include "built_ins.h"
#include <asm-generic/errno-base.h>
#include <errno.h>

void	safely_del_node(t_token_stream_node **node)
{
	t_token_stream_node	*temp;

	temp = *node;
	*node = (*node)->next;
	ft_del_node(&temp);
}
