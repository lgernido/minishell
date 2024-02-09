/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fonctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:03:10 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/09 17:03:11 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "minishell.h"

static int	is_invalid(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (1);
	return (0);
}

static int	is_the_end_of_string(char c)
{
	int	ret_value;

	ret_value = 0;
	if (c == '\0')
	{
		ret_value = 1;
	}
	return (ret_value);
}

static int	is_invalid_character_for_naming_var(char c, char *str)
{
	int	ret_value;

	ret_value = 0;
	if (is_invalid(c))
	{
		ft_printf_err("minishell: export: `%s':\
				not a valid identifier\n", str);
		ret_value = 1;
	}
	return (ret_value);
}

static int	does_the_value_have_valid_content(char c)
{
	int	ret_value;

	ret_value = 0;
	if (c == '\0')
	{
		ret_value = 1;
	}
	return (ret_value);
}

int	parse_before_equal_sign(char *str)
{
	size_t	i;
	int		ret_value;

	i = 0;
	ret_value = 0;
	while (str[i] != '=' && ret_value != 1)
	{
		ret_value = is_invalid_character_for_naming_var(str[i], str);
		i++;
		ret_value = is_the_end_of_string(str[i]);
	}
	if (ret_value == 0)
	{
		ret_value = does_the_value_have_valid_content(str[i + 1]);
	}
	return (ret_value);
}
