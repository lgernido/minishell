/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:51:21 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/03 17:51:21 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	get_number_of_args(char **av)
{
	int	i;

	i = 0;
	if (av && *av)
	{
		while (av[i])
			i++;
	}
	return (i);
}

int	is_set(char *str)
{
	while (*str && *str != '=')
		str++;
	if (!*str)
		return (0);
	str++;
	if (*str == -1)
		return (0);
	return (1);
}

t_bool	is_the_var(char *var, char *env)
{
	if (ft_strncmp(var, env, ft_strlen(var)))
		return (FALSE);
	return (TRUE);
}

void	print_export(char **env)
{
	while (*env)
	{
		if (is_set(*env))
			printf("declare -x \"%s\"\n", *env);
		env++;
	}
}

char	*ft_getenv(t_core *core, char *var)
{
	int	i;
	int	len;

	i = 0;
	var++;
	len = ft_strlen(var);
	if (!ft_strncmp(var, "?", 2))
		return (ft_itoa(core->error_code));
	while (core->env[i])
	{
		if (!ft_strncmp(core->env[i], var, len))
		{
			if (*(core->env[i] + len + 1) != -1)
				return (ft_strdup(core->env[i] + len));
		}
		i++;
	}
	return (NULL);
}
