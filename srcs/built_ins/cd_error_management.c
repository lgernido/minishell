/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:12:44 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/08 14:12:47 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "clean_and_error.h"

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
