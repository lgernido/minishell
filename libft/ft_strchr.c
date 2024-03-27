/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:38:46 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/10 14:56:48 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const unsigned char	*p;
	int					i;
	char				cs;

	i = 0;
	p = (const unsigned char *)s;
	cs = (char)c;
	while (*(p + i))
	{
		if (*(p + i) == cs)
		{
			return ((char *)p + i);
		}
		i++;
	}
	if (c == 0)
		return ((char *)p + i);
	return (0);
}

static int	iterate_through_charset(const char current_char,
		const char *charset)
{
	size_t	i;
	int		return_value;

	i = 0;
	return_value = 0;
	while (charset[i] != '\0' && return_value == 0)
	{
		if (charset[i] == current_char)
		{
			return_value = 1;
		}
		++i;
	}
	return (return_value);
}

char	*ft_strchr_charset(const char *s, const char *charset)
{
	const unsigned char	*p;
	int					i;

	i = 0;
	p = (const unsigned char *)s;
	while (*(p + i))
	{
		if (iterate_through_charset(*(p + i), charset) == 1)
		{
			break ;
		}
		i++;
	}
	return ((char *)p + i);
}

/*#include <stdio.h>

int	main (void)
{
	char *s = "abBa";
	printf("%s\n", ft_strchr(s, 66));
}*/
