/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:16:23 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 09:51:44 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_core(t_core *core)
{
	core->error_code = 0;
	core->ast = NULL;
	core->env = NULL;
	core->token_list = NULL;
}
