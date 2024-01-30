/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:53:53 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/10 13:41:39 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_sub(size_t len, size_t *f, const char *little,
	const char *big)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = *f;
	while (little[j] && little[j] == big[i] && i < len)
	{
		i++;
		j++;
	}
	if (little[j] == 0)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	f;

	i = 0;
	f = 0;
	if (len == 0 && big == NULL)
		return (NULL);
	if (little[i] == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{	
		f = i;
		if (big[i] == little[0] && check_sub(len, &f, little, big))
			return ((char *)big + f);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
int main(void)
{
	char *big = "";
	char *little = "tati";
	printf("%s\n", ft_strnstr(big, little, 11));
}*/
