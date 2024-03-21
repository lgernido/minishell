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
#include "built_ins.h"
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

t_bool	is_set(char *str)
{
	if (str)
		return (TRUE);
	return (FALSE);
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

size_t	get_var_name_len(char	*var)
{
	size_t	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
	{
		++i;
	}
	return (i);
}

t_bool	match_var(char *searched_var, char *looked_var)
{
	const size_t	len = get_var_name_len(looked_var);
	t_bool	return_value;

	return_value = FALSE;
	looked_var[len] = '\0';
	if (ft_strncmp(searched_var, looked_var, len + 1) == 0)
	{
		return_value = TRUE;
	}
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
