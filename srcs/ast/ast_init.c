/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:21:37 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/12 12:21:37 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"

void	ast_init(t_token_stream_node *token_stream, t_core *core)
{
	core->ast = ast_new_node();
	if (core->ast == NULL)
		ft_clean_exit(core, MALLOC);
}

/* So : - go trough token_stream till logical opertor -- good
				- copy in the node from start to this point --> ft_lst_n_cpy ? 
