/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:34:54 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/06 17:34:57 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"
#include "clean_and_error.h"

static char	*ft_home_sweet_home(t_core *core)
{
	char	*home;

	home = ft_getenv(core, "$HOME");
	if (!home)
	{
		if (errno == ENOMEM)
			ft_clean_exit(core, MALLOC);
	}
	return (home);
}

int	go_specified_dir(void *path)
{
	const int	return_value = chdir(path);

	if (return_value == -1)
	{
		throw_error_message(path, error_while_shifting_directory);
	}
	else
	{
		return (0);
	}
	return (return_value);
}

static int	search_home_in_env(t_core *core)
{
	const char	*home = ft_home_sweet_home(core);
	int			return_value;

	if (!home)
	{
		return_value = throw_error_message(NULL, home_not_set);
	}
	else
	{
		return_value = go_specified_dir((char *)home);
		free((char *)home);
	}
	return (return_value);
}

int	act_according_to_arg_number(t_core *core, int ac, char **av)
{
	int	return_value;

	if (ac == 0)
	{
		return_value = 1;
	}
	else if (ac > 2)
	{
		return_value = throw_error_message(NULL, too_many_args);
	}
	else if (ac == 1)
	{
		return_value = search_home_in_env(core);
	}
	else
	{
		return_value = go_specified_dir(av[1]);
	}
	return (return_value);
}

int	ft_cd(char **av, t_core *core)
{
	int			ac;
	int			return_value;
	char		*old_pwd;

	old_pwd = get_pwd_in_buffer(core);
	ac = get_number_of_args(av);
	return_value = act_according_to_arg_number(core, ac, av);
	if (return_value == 0)
	{
		update_env_var(core, old_pwd);
	}
	return (return_value);
}
