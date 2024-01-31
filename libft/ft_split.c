/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:25:50 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/13 10:47:22 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cw(const char *s, char c)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	if (s[0] == 0 || s[0] != c)
		nb++;
	while (s[i])
	{
		if ((s[i] == c || s[i] == 0) && (s[i + 1] != c && s[i + 1] != 0))
			nb++;
		i++;
	}
	return (nb);
}

static void	free_tab(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	ft_write_str(char *dest, const char *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return ;
}

static void	ft_fill_tab(char **str_tab, const char *s, char c)
{
	int	i[2];
	int	count;

	i[0] = 0;
	count = 0;
	while (s[i[0]])
	{
		if (s[i[0]] != c && s[i[0]] != 0)
		{
			i[1] = i[0];
			while (s[i[1]] != c && s[i[1]])
				i[1]++;
			str_tab[count] = malloc((i[1] - i[0] + 1) * sizeof (char));
			if (str_tab[count] == NULL)
			{
				free_tab(str_tab, count - 1);
				return ;
			}
			ft_write_str(str_tab[count], s + i[0], i[1] - i[0]);
			i[0] = i[1] - 1;
			count++;
		}
		i[0]++;
	}
	return ;
}

char	**ft_split(char const *s, char c)
{
	char	**str_tab;
	int		n;

	if (!s)
		return (NULL);
	n = ft_cw(s, c);
	if (ft_strlen(s) == 0)
		n = 0;
	str_tab = malloc((n + 1) * sizeof (char *));
	if (str_tab == NULL)
		return (NULL);
	str_tab[n] = NULL;
	ft_fill_tab(str_tab, s, c);
	return (str_tab);
}
