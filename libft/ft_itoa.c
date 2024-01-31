/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:11:10 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/10 13:40:37 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_retrieve_length(int n, size_t	*len)
{
	if (n == -2147483648)
	{
		*len = 10;
		return ;
	}
	if (n > 9)
		ft_retrieve_length(n / 10, len);
	*len += 1;
	return ;
}

static void	fill_str(char	*str, size_t	*f, int n)
{
	if (n == -2147483648)
	{
		n -= 1;
		str[10] += 1;
	}
	if (n > 9)
		fill_str(str, f, n / 10);
	str[*f] += n % 10 + 48;
	*f += 1;
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	f;
	size_t	len;

	f = 0;
	len = 0;
	if (n < 0)
	{
		f = 1;
		n *= -1;
	}
	ft_retrieve_length(n, &len);
	len += f;
	str = ft_calloc((len + 1), sizeof (char));
	if (str != NULL)
	{
		str[len] = 0;
		if (f == 1)
			str[0] = '-';
		fill_str(str, &f, n);
	}
	return (str);
}

/*#include <stdio.h>

int	main(void)
{
	char	*str;
	str = ft_itoa(-2147483648);
	printf("%s\n", str);
	free(str);
	return (0);
}*/
