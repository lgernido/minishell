/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:35:44 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/05 16:35:45 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	is_invalid(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (1);
	return (0);
}

static int	parse_var(char *str)
{
	while (*str != '=')
	{
		if (is_invalid(*str))
		{
			ft_printf_err("minishell: export: `%s':\
not a valid identifier\n", str);
			return (1);
		}
		str++;
		if (!*str)
			return (1);
	}
	if (!*str + 1)
		return (1);
	return (0);
}

char	**ft_realloc_env(char **env, int *size)
{
	char	**new_envp;

	new_envp = ft_calloc(*size * 2, sizeof(char *));
	if (!new_envp)
	{
		ft_free_tab(env);
		return (NULL);
	}
	while (*env)
	{
		*new_envp = *env;
		env++;
		new_envp++;
	}
	free(env);
	*size *= 2;
	return (new_envp);
}

char	*get_valid_addr(t_core *core)
{
	int	i;

	i = 0;
	while (*(core->env) && i < core->env_size - 1)
		i++;
	if (i < core->env_size - 1)
		return (*(core->env) + i);
	else
	{
		core->env = ft_realloc_env(core->env, &core->env_size);
		if (!core->env)
			return (NULL);
		return (get_valid_addr(core));
	}
}

int	ft_export(char **av, t_core *core)
{
	char	*addr;

	av++;
	while (*av)
	{
		if (!parse_var(*av))
		{
			addr = get_valid_addr(core);
			if (!addr)
				ft_clean_exit(core, MALLOC);
			addr = ft_strdup(*av);
		}
		av++;
	}
	return (0);
}
