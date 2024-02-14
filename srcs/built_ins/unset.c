/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:03:33 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/05 15:45:46 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "built_ins.h"

static int	unset_var(char *var, char **env)
{
	const size_t	len = ft_strlen(var);

	while (*env)
	{
		if (!ft_strncmp(var, *env, len))
		{
			free (*env);
			*env = NULL;
			break ;
		}
		env++;
	}
	return (0);
}

int	ft_unset(char **av, t_core *core)
{
	if (!av)
		return (0);
	av++;
	while (*av)
	{
		if (unset_var(*av, core->env))
			ft_clean_exit(core, MALLOC);
		av++;
	}
	return (0);
}
