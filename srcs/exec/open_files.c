/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:22:59 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/13 17:23:00 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "clean_and_error.h"

int	open_input(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	return (fd);
}

int	open_output(char *path)
{
	int	fd;

	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 00244 | 00400);
	if (fd == -1)
	{
		fd = open(path, O_WRONLY | O_TRUNC, 00244 | 00400);
	}
	return (fd);
}

int	open_append(char *path)
{
	int	fd;

	fd = open(path, O_RDWR | O_CREAT | O_APPEND, 00244 | 00400);
	if (fd == -1)
	{
		fd = open(path, O_WRONLY | O_APPEND, 00244 | 00400);
	}
	return (fd);
}

int	open_file(char *path, int (*open_function)(char *))
{
	int	fd;

	fd = open_function(path);
	if (fd == -1)
	{
		throw_error_message(path, exec_error);
	}
	return (fd);
}
