/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:31:38 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/05 11:31:38 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"

static void	check_sign(char *str, int *sign, int *i)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign *= -1;
		*i += 1;
	}
}

unsigned char	ex_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32)
		i++;
	check_sign(str, &sign, &i);
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	if (str[i])
	{
		ft_printf_err("minishell: exit: %s: numeric argument required\n", str);
		return (2);
	}
	printf("exit\n");
	return (res * sign);
}

int	ft_exit(char **av, t_core *core)
{
	int	ac;

	ac = get_number_of_args(av);
	if (ac == 1)
	{
		printf("exit\n");
		ft_clean_exit(core, core->error_code);
	}
	if (ac == 2)
	{
		ft_clean_exit(core, ex_atoi(av[1]));
	}
	ft_printf_err("exit\nminishell: exit: too many arguments\n");
	return (1);
}
