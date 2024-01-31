/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:03:54 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/09 09:35:41 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	idx;
	size_t	f;
	char	cs;

	i = 0;
	f = 0;
	idx = 0;
	cs = (char)c;
	while (s[i])
	{
		if (s[i] == cs)
		{
			f = 1;
			idx = i;
		}
		i++;
	}
	if (c == 0)
		return ((char *)s + i);
	else if (f == 1)
		return ((char *)s + idx);
	return (NULL);
}

/*#include <stdio.h>
int main(void)
{
	char *s = "aBBBBBAb";
	printf("%s\n", ft_strrchr(s, 66));
}*/
