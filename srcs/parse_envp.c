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

	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (1);
		i++;
	}
	return (0);
}

void	parse_envp(char **envp, t_core *core)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	core->env = ft_calloc(i * 2, sizeof(char *));
	if (!core->env)
		ft_clean_exit(core, MALLOC);
	core->env_size = i * 2;
	if (fill_arr(envp, core->env))
		ft_clean_exit(core, MALLOC);
	return ;
}
