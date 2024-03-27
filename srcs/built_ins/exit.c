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
#include "printerr.h"

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
	if (ft_strlen(&str[i]) > 9 || str[i] == '\0')
		return (ft_printf_err("minishell: exit: %s: numeric \
argument required\n", str), 2);
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	if (str[i])
		return (ft_printf_err("minishell: exit: %s: numeric \
argument required\n", str), 2);
	printf("exit\n");
	return (res * sign);
}

void	multi_arg(t_core *core, char **av)
{
	unsigned char	is_first_arg_valid;
	int				return_check;

	return_check = ft_atoi(*av);
	is_first_arg_valid = ex_atoi(*av);
	if (is_first_arg_valid == 2 && return_check != 2)
	{
		ft_clean_exit(core, 2);
	}
}

int	ft_exit(char **av, t_core *core)
{
	int	ac;

	ac = get_number_of_args(av);
	if (ac == 1)
<<<<<<< HEAD
		ft_clean_exit(core, core->error_code);
	if (ac == 2)
=======
	{
		printf("exit\n");
		ft_clean_exit(core, core->error_code);
	}
	if (ac == 2)
	{
>>>>>>> lucie
		ft_clean_exit(core, ex_atoi(av[1]));
	}
	if (ac > 2)
	{
		multi_arg(core, &av[1]);
	}
	ft_printf_err("exit\nminishell: exit: too many arguments\n");
	return (1);
}
