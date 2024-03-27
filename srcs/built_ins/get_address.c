/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_address.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:34:42 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 13:34:43 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"

char	**ft_realloc_env(char **env, int *size)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = ft_calloc(*size * 2, sizeof(char *));
	if (!new_envp)
	{
		ft_free_tab(env);
		return (NULL);
	}
	while (i < *size)
	{
		new_envp[i] = env[i];
		i++;
	}
	free(env);
	*size *= 2;
	return (new_envp);
}

char	**get_in_use_address(char *to_comp, t_core *core)
{
	int	i;

	i = 0;
	while (i < core->env_size - 1)
	{
		if (core->env[i] != NULL)
		{
			if (is_the_var(to_comp, core->env[i]))
				return (&core->env[i]);
		}
		++i;
	}
	return (NULL);
}

char	**get_unused_address(t_core *core)
{
	int		i;

	i = 0;
	while (i < core->env_size)
	{
		if (core->env[i] == NULL)
		{
			return (&core->env[i]);
		}
		++i;
	}
	core->env = ft_realloc_env(core->env, &core->env_size);
	if (!core->env)
		ft_clean_exit(core, MALLOC);
	return (get_unused_address(core));
}

char	**get_valid_addr(t_core *core, char *av)
{
	char	**to_comp;
	char	**to_return;

	to_comp = ft_split(av, '=');
	if (!to_comp)
		ft_clean_exit(core, MALLOC);
	to_return = get_in_use_address(to_comp[0], core);
	ft_free_tab(to_comp);
	if (to_return == NULL)
	{
		return (get_unused_address(core));
	}
	return (to_return);
}
