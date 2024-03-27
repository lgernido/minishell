/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:29:50 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/06 15:29:50 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "printerr.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include "built_ins.h"
#include <stdio.h>
#include <unistd.h>

static int	check_option(char **av)
{
	int	ac;

	ac = get_number_of_args(av);
	if (ac < 2)
		return (TRUE);
	if (*av[1] == '-' && ft_strlen(av[1]) > 1)
	{
		ft_printf_err("minishell: pwd: -%c: invalid option\n\
pwd: usage: pwd [NONE]\n", av[1][1]);
		return (FALSE);
	}
	return (TRUE);
}

static	int	buffer_check(char	*pwd, t_core *core)
{
	if (pwd == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	if (ft_strlen(pwd) == 0)
	{
		return (1);
	}
	return (0);
}

static int	retrieve_pwd(t_core *core)
{
	char	*pwd;
	int		ret_value;

	pwd = get_pwd_in_buffer(core);
	ret_value = buffer_check(pwd, core);
	if (ret_value == 0)
	{
		printf("%s\n", pwd);
	}
	free(pwd);
	return (ret_value);
}

int	ft_pwd(char **av, t_core *core)
{
	int		ret_value;

	(void)av;
	ret_value = 0;
	if (check_option(av) == FALSE)
	{
<<<<<<< HEAD
		ret_value = 2;
=======
		free(buffer);
		if (errno == ENOMEM)
			ft_clean_exit(core, MALLOC);
		return (1);
>>>>>>> lucie
	}
	if (ret_value == 0)
	{
		ret_value = retrieve_pwd(core);
	}
	return (ret_value);
}
