/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:46:27 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/09 13:46:28 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"

static char	*ft_realloc_buffer(char *buffer, int len)
{
	char	*new_buf;

	new_buf = ft_calloc(len + 1, sizeof(char));
	free(buffer);
	return (new_buf);
}

static char	*get_pwd(char *buffer, int len)
{
	if (len >= BUFFER_LIMIT)
	{
		ft_printf_err("minishell: pwd: size of path \
exceed buffer limit (4096 bytes)");
		return (buffer);
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
		return (buffer);
	}
}

char	*get_pwd_in_buffer(t_core *core)
{
	char	*pwd;

	pwd = ft_calloc(PWD_BUFFER + 1, sizeof(char));
	if (pwd == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	get_pwd(pwd, PWD_BUFFER);
	if (pwd == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	return (pwd);
}
