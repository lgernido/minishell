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

static int	unset_var(char *var, char **env)
{
	char	*new_var;
	size_t	len;

	len = ft_strlen(var);
	while (*env)
	{
		if (!ft_strncmp(var, *env, len))
		{
			new_var = ft_calloc(len + 3, sizeof (char));
			if (!new_var)
				return (1);
			ft_strlcpy(new_var, *env, len + 1);
			new_var[len] = '=';
			new_var[len + 1] = -1;
			free(*env);
			*env = new_var;
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
