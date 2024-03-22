/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:52:00 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/05 10:52:01 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_arr(char **src, char **dest)
{
	int	i;
	int	return_value;

	i = 0;
	return_value = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (dest[i] == NULL)
		{
			return_value = 1;
			break;
		}
		i++;
	}
	return (return_value);
}

static int	env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		++i;
	}
	return (i);
}

static	void	set_up_envp(t_core *core, const int size)
{
	core->env = ft_calloc(size, sizeof(char *));
	if (core->env == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	core->env_size = size;
	return ;
}

void	handle_envp(char **envp, t_core *core)
{
	const int	size_of_env = env_size(envp);

	if (size_of_env == 0)
	{
		set_up_envp(core, 8);
	}
	else
	{
		set_up_envp(core, size_of_env * 2);
		fill_arr(envp, core->env);
	}
	return ;
}
