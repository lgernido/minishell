/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_updtae_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:59:12 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/08 15:59:13 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"

void	update_env_var(t_core	*core, char *old_pwd)
{
	char	*new_pwd;

	swap_var(core, old_pwd, "OLDPWD");
	new_pwd = get_pwd_in_buffer(core);
	swap_var(core, new_pwd, "PWD");
}
