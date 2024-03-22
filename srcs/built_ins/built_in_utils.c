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
	size_t	i;

	i = 0;
	if (str == NULL)
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '=')
		{
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

t_bool	is_the_var(char *var, char *env)
{
	if (ft_strncmp(var, env, ft_strlen(var)))
		return (FALSE);
	return (TRUE);
}
