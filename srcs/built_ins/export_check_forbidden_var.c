/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_forbidden_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:26:05 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/09 17:26:35 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"

int	check_len(char *str)
{
	const size_t	len = ft_strlen(str);
	int				ret_value;

	ret_value = 0;
	if (len < 2)
	{
		ret_value = 1;
	}
	return (ret_value);
}

int	is_the_var_write_protected(char	*str)
{
	const int	comparison_return = ft_strncmp(str, "_=", 2);
	int			ret_value;

	ret_value = 0;
	if (comparison_return == 0)
	{
		ret_value = 1;
	}
	return (ret_value);
}
