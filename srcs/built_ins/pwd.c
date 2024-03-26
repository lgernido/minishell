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
		return (0);
	if (*av[1] == '-' && ft_strlen(av[1]) > 1)
	{
		ft_printf_err("minishell: pwd: -%c: invalid option\n\
pwd: usage: pwd [NONE]\n", av[1][1]);
		return (1);
	}
	return (0);
}

char	*ft_realloc_buffer(char *buffer, int len)
{
	char	*new_buf;

	new_buf = ft_calloc(len + 1, sizeof(char));
	free(buffer);
	return (new_buf);
}

char	*get_pwd(char *buffer, int len)
{
	if (len >= BUFFER_LIMIT)
	{
		ft_printf_err("minishell: pwd: size of path \
exceed buffer limit (4096 bytes)");
		return (NULL);
	}
	buffer = getcwd(buffer, len);
	if (buffer)
		return (buffer);
	if (errno == ERANGE)
	{
		buffer = ft_realloc_buffer(buffer, len * 2);
		if (!buffer)
			return (NULL);
		return (get_pwd(buffer, len * 2));
	}
	else
	{
		ft_printf_err("pwd: error retrieving current directory: getcwd\
: cannot access parent directories: No such file or directory\n");
		return (NULL);
	}
}

int	ft_pwd(char **av, t_core *core)
{
	char	*buffer;
	int		len;

	(void)av;
	if (check_option(av))
		return (2);
	len = PWD_BUFFER;
	buffer = ft_calloc(len + 1, sizeof(char));
	if (!buffer)
		ft_clean_exit(core, MALLOC);
	if (!get_pwd(buffer, len))
	{
		free(buffer);
		if (errno == ENOMEM)
			ft_clean_exit(core, MALLOC);
		return (1);
	}
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}
