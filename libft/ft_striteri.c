/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:42:34 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/10 13:44:03 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}

/*char	ft_test(unsigned int i, char *s)
{
	char	c;

	c = s[i + 1];
	return (c);
}

#include <stdio.h>
int	main(void)
{
	char str[27] = "abcdefghijklmnopqrstuvwxyz";
	ft_striteri(str, &ft_test);
	printf("%s\n", str);
	return (0);
}*/
