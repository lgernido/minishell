/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:43:46 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/08 12:15:25 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_p;
	unsigned char		*dest_p;

	src_p = src;
	dest_p = dest;
	if (dest == NULL && src == NULL && n != 0)
		return (dest);
	while (n > 0)
	{
		*dest_p++ = *src_p++;
		n--;
	}
	return (dest);
}

/*#include <stdio.h>

int	main(void)
{
	char src[15] = "Salut";
	char dest[20] = "hhhhhhhhhhh";
	ft_memcpy(dest, src, 3);
	printf("%s\n", dest);
}*/
