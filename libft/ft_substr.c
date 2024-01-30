/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:26:49 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/10 14:00:37 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	absolute_len;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		str = malloc(1 * sizeof (char));
		if (str != NULL)
			*str = 0;
		return (str);
	}
	absolute_len = ft_strlen(s + start);
	if (len > absolute_len)
		len = absolute_len;
	str = malloc(len + 1 * sizeof (char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

/*#include <stdio.h>
int	main(void)
{
	char	*s = ft_strdup("1");
	char *substr = ft_substr(s, 42, 42000000);
	//printf("%s\n", substr);
	free(substr);
	free (s);
}*/
