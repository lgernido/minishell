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

char	*ft_getenv(t_core *core, char *var)
{
	int				i;
	const size_t	len = ft_strlen(var) - 1;

	i = 0;
	var++;
	if (!ft_strncmp(var, "?", 2))
		return (ft_itoa(core->error_code));
	while (core->env[i])
	{
		if (!ft_strncmp(core->env[i], var, len))
			return (ft_strdup(core->env[i] + 1 + len));
		i++;
	}
	return (NULL);
}
