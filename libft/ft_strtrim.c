/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:13:32 by vlevy             #+#    #+#             */
/*   Updated: 2024/03/12 09:48:10 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_check(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i] || c == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_blank(char *str)
{
	str = malloc(1 * sizeof(char));
	if (str != NULL)
		*str = 0;
	return (str);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*strimed_str;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	j = len - 1;
	strimed_str = NULL;
	while (char_check(s1[i], set) && s1[i])
		i++;
	if (i >= j)
		return (ft_blank(strimed_str));
	while (char_check(s1[j], set))
		j--;
	j = len - j - 1;
	strimed_str = malloc((len - (i + j) + 1) * sizeof(char));
	if (strimed_str != NULL)
		ft_strlcpy(strimed_str, s1 + i, len - (i + j - 1));
	return (strimed_str);
}

/*#include <stdio.h>
int	main(void)
{
	char	*s = ft_strtrim("adfgggfdffgdfddffddaaaag", "adfg");
	printf("%s\n", s);
	free(s);
	return (0);
}*/
