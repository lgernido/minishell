/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:32:33 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/08 17:54:50 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_p;
	const unsigned char	*s2_p;

	s1_p = s1;
	s2_p = s2;
	if (n == 0)
		return (0);
	while (n - 1 > 0 && *s1_p == *s2_p)
	{
		s1_p++;
		s2_p++;
		n--;
	}
	return (*s1_p - *s2_p);
}

/*#include <stdio.h>
int	main(void)
{
	char *s1 = "Hello";
	char *s2 = "Hello";
	printf("%d\n", ft_memcmp(s1, s2, 5));
}*/
