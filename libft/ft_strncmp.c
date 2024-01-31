/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:13:32 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/09 11:18:46 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*us1;
	const unsigned char	*us2;
	size_t				i;

	i = 0;
	us1 = (const unsigned char *)s1;
	us2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((*us1 || *us2) && *us1 == *us2 && i < n - 1)
	{
		i++;
		us1++;
		us2++;
	}
	return (*us1 - *us2);
}
/*#include <stdio.h>

int main(void)
{
	printf("%d\n", ft_strncmp("Tripouille", "TripouilleX", 42));
	return 0;
}*/
