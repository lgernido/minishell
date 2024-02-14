/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:25:50 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/05 14:25:51 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"
#include "printerr.h"

int	ft_env(char **av, t_core *core)
{
	int	ac;
	int	i;

	i = 0;
	ac = get_number_of_args(av);
	if (ac > 1)
		ft_printf_err("env: ‘%s’: No such file or directory", av[1]);
	while (core->env[i])
	{
		if (is_set(core->env[i]) == TRUE)
			printf("%s\n", core->env[i]);
		i++;
	}
	return (0);
}
