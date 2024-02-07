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

#include "libft.h"
#include "minishell.h"
#include "printerr.h"
#include <asm-generic/errno-base.h>
#include <string.h>
#include <unistd.h>

static char	*ft_home_sweet_home(t_core *core)
{
	char	*home;

	home = ft_getenv(core, "$HOME");
	if (!home)
	{
		if (errno != ENOMEM)
			ft_printf_err("minshell: cd: HOME not set\n");
	}
	return (home);
}

void	update_env(t_core *core)
{
	char	*pwd;
	char	*joined_str;
	char	**addr;

	addr = get_valid_addr(core, "OLDPWD=");
	if (*addr)
		free(*addr);
	pwd = ft_getenv(core, "$PWD");
	if (!pwd)
		return ;
	joined_str = ft_strjoin("PWD=", pwd);
	if (!joined_str)
	{
		free(pwd);
		return ;
	}
	*addr = ft_strdup(joined_str);
	free(pwd);
	free(joined_str);
}

int	change_dir(char *path, t_core *core, int home)
{
	if (chdir(path) != 0)	
	{
		ft_printf_err("minishell: cd: %s:%s", strerror(errno), path);
		if (home)
			free(path);
		return (1);
	}
	if (home)
		free(path);
	update_env
	return (0);
}

int	ft_cd(char **av, t_core *core)
{
	int		ac;
	char	*home;

	home = NULL;
	ac = get_number_of_args(av);
	if (ac == 0)
		return (1);
	else if (ac > 2)
	{
		ft_printf_err("minishell: cd: too many arguments\n");
		return (1);
	}
	else if (ac == 1)
	{
		home = ft_home_sweet_home(core);
		if (!home)
		{
			if (errno == ENOMEM)
				ft_clean_exit(core, MALLOC);
			return (1);
		}
		return (change_dir(home, core, 1));
	}
	return (change_dir(*(av + 1), core, 0));
}
