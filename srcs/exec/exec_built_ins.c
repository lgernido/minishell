/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:40:59 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/05 09:41:00 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"
#include "exec.h"

void	init_built_ins_tab(t_built_ins *built_ins_tab)
{
	built_ins_tab[0] = ft_env;
	built_ins_tab[1] = ft_export;
	built_ins_tab[2] = ft_unset;
	built_ins_tab[3] = ft_cd;
	built_ins_tab[4] = ft_pwd;
	built_ins_tab[5] = ft_exit;
	built_ins_tab[6] = ft_echo;
	return ;
}

void	exec_built_ins(t_core *core, t_command_node *current_command,
		int command_index)
{
	t_built_ins	built_in_tab[7];

	init_built_ins_tab(built_in_tab);
}
