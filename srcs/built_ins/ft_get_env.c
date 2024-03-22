/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:26:17 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 13:26:18 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_var_name_len(char	*var)
{
	size_t	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
	{
		++i;
	}
	return (i);
}

static t_bool	match_var(char *searched_var, char *looked_var)
{
	const size_t	len = get_var_name_len(looked_var);
	const char		end_of_var = looked_var[len];
	t_bool			return_value;

	return_value = FALSE;
	looked_var[len] = '\0';
	if (ft_strncmp(searched_var, looked_var, len + 1) == 0)
	{
		return_value = TRUE;
	}
	looked_var[len] = end_of_var;
	return (return_value);
}

char	*ft_getenv(t_core *core, char *var)
{
	int				i;
	const size_t	len = ft_strlen(var) - 1;

	i = 0;
	var++;
	if (!ft_strncmp(var, "?", 2))
	{
		return (ft_itoa(core->error_code));
	}
	while (i < core->env_size)
	{
		if (core->env[i] != NULL && match_var(var, core->env[i]) == TRUE)
		{
			return (ft_strdup(core->env[i] + 1 + len));
		}
		i++;
	}
	return (NULL);
}
