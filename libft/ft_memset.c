/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:40:21 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/07 09:44:08 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p++ = (unsigned char)c;
		n--;
	}
	return (s);
}

/*#include <stdio.h>
int	main(void)
{
	char s[100] = "Salut l'equipe sa di koi aujourd'hui ?";
	ft_memset(s + 10, 66, 10);
	printf("%s\n", s);
	int n = 10;
	int arr[n];
	ft_memset(arr, 1, 10);
	int i = 0;
	while (i < 10)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
	return (0);
}*/
