/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:44:18 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/09 10:51:02 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = (ft_strlen(s1));
	len2 = (ft_strlen(s2));
	str = malloc((len1 + len2 + 1) * sizeof (char));
	if (str != NULL)
	{
		ft_strlcpy(str, s1, len1 + 1);
		ft_strlcat(str, s2, len1 + len2 + 1);
	}
	return (str);
}

/*#include <stdio.h>
int	main(void)
{
	char *s1 = "Salut";
	char	*s2 = "ca va ?";
	char	*join = ft_strjoin(s1, s2);
	printf("%s\n", join);
	free(join);
}*/
