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
	while (env[i])
	{
		new_envp[i] = env[i];
		i++;
	}
	free(env);
	*size *= 2;
	return (new_envp);
}

char	**get_valid_addr(t_core *core, char *av)
{
	int		i;
	char	**to_comp;

	i = 0;
	to_comp = ft_split(av, '=');
	if (!to_comp)
		ft_clean_exit(core, MALLOC);
	while (core->env[i] != NULL && i < core->env_size - 1)
	{
		if (is_the_var(*to_comp, core->env[i]))
			break ;
		++i;
	}
	ft_free_tab(to_comp);
	if (i < core->env_size - 1)
		return (&core->env[i]);
	else
	{
		core->env = ft_realloc_env(core->env, &core->env_size);
		if (!core->env)
			ft_clean_exit(core, MALLOC);
		return (get_valid_addr(core, av));
	}
}
