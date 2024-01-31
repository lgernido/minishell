/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:52:54 by vlevy             #+#    #+#             */
/*   Updated: 2023/12/01 19:05:59 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = malloc(len + 1 * sizeof (char));
	if (str != NULL)
		ft_strlcpy(str, s, len + 1);
	return (str);
}

/*int	main(void)
{
	char *s = "Salut l'equipe";
	char *str = ft_strdup(s);
	free(str);
	return(0);
}*/
