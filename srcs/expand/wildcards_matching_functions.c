/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_matching_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:28:11 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/21 17:28:11 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	match_wildcard_entry(char **big, const char *little)
{
	const size_t	little_len = ft_strlen(little);
	const size_t	big_len = ft_strlen(*big);
	const char		*little_location = ft_strnstr(*big, little, big_len);
	t_bool			return_value;

	if (little_location == NULL)
	{
		return_value = FALSE;
	}
	else
	{
		return_value = TRUE;
		*big = (char *)little_location + little_len;
	}
	return (return_value);
}

t_bool	check_end_of_string(char *big, char *little)
{
	const size_t	big_len = ft_strlen(big);
	const size_t	little_len = ft_strlen(little);
	const char		*little_location = ft_strnstr(&big[big_len - little_len],
			little, little_len);
	t_bool			return_value;

	return_value = TRUE;
	if (little_location == NULL)
	{
		return_value = FALSE;
	}
	return (return_value);
}

t_bool	check_beginning_of_string(char	*big, char *little)
{
	const size_t	len = ft_strlen(little);
	const char		*little_location = ft_strnstr(big, little, len);
	t_bool			return_value;

	return_value = TRUE;
	if (little_location == NULL)
	{
		return_value = FALSE;
	}
	return (return_value);
}
