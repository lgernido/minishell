/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:12:44 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/07 09:44:25 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	size_t	i;
	int		f;
	int		result;

	i = 0;
	f = 1;
	result = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			f *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + s[i] - 48;
		i++;
	}
	return (result * f);
}

/*#include <stdio.h>

int	main(void)
{
	printf("%d\n%d\n%d\n%d\n", ft_atoi("        759"), ft_atoi("      -44"),
	ft_atoi("---55"), ft_atoi("+-+--789"));
}*/
