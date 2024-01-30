/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:30:03 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/13 10:45:44 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;
	unsigned int	len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	str = ft_calloc(len + 1, sizeof (char));
	if (str == NULL)
		return (str);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}

/*char	ft_test(unsigned int i, char c)
{
	c += i;
	return (c);
}

#include <stdio.h>
int	main(void)
{
	char *s = "abcdefghijklmnopqrstuvwxyz";
	char	*str = ft_strmapi(s, &ft_test);
	printf("%s\n", str);
	free(str);
}*/
