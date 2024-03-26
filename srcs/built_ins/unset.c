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

static int	unset_var(char *var, char **env, size_t env_size)
{
	const size_t	len = ft_strlen(var);
	size_t			i;

	i = 0;
	if (ft_strncmp("_", var, 2) == 0)
	{
		return (0);
	}
	while (i < env_size)
	{
		if (env[i] != NULL)
		{
			if (!ft_strncmp(var, env[i], len))
			{
				free (env[i]);
				env[i] = NULL;
				break ;
			}
		}
		++i;
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
		if (unset_var(*av, core->env, core->env_size))
			ft_clean_exit(core, MALLOC);
		av++;
	}
	return (0);
}
