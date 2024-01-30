/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:08:08 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/08 15:50:46 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char			*dest_p;
	const unsigned char		*src_p;

	dest_p = dest;
	src_p = src;
	if (dest == NULL && src == NULL && n != 0)
		return (dest);
	if (dest > src)
	{
		while (n != 0)
		{
			*(dest_p + n - 1) = *(src_p + n - 1);
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

/*int	main(void)
{
	char src[50]="hhhhhhhhhhhh";
	char dest[50]="jjjjjjjjjjjjjj";
	ft_memmove(dest, src, 3);
}*/
