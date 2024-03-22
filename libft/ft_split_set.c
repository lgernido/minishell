/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:25:50 by vlevy             #+#    #+#             */
/*   Updated: 2023/07/12 17:48:23 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	char_check(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i] || c == 0)
			return (1);
		i++;
	}
	return (0);
}

int	hm_str(char *str, char *charset, int nb)
{
	int				i;

	i = 0;
	if (!char_check(str[0], charset))
		nb++;
	while (str[i])
	{
		if ((char_check(str[i], charset)) && (!char_check(str[i + 1], charset)))
			nb++;
		i++;
	}
	return (nb);
}

char	*fill_string_again(char *str, char *splited, int *stream, int i)
{
	int					j;

	splited = malloc((i + 1) * sizeof (char));
	if (splited == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		splited[j] = str[*stream];
		j++;
		*stream += 1;
	}
	splited[j] = 0;
	return (splited);
}

char	*fill_string(char *str, char *charset, char *splited, int *stream)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (str[*stream])
	{
		if (!char_check(str[*stream], charset))
		{
			j = *stream;
			while (!char_check(str[j], charset) && str[j])
			{
				i++;
				j++;
			}
			break ;
		}
		*stream += 1;
	}
	splited = fill_string_again(str, splited, stream, i);
	*stream = j + 1;
	return (splited);
}

char	**ft_split_set(char *str, char *charset)
{
	int					s_num;
	char				**splited_str;
	int					i;
	int					stream;

	stream = 0;
	s_num = 0;
	s_num = hm_str(str, charset, s_num);
	splited_str = ft_calloc((s_num + 1), (sizeof (char *)));
	if (splited_str == NULL)
		return (NULL);
	i = 0;
	while (i < s_num)
	{
		splited_str[i] = fill_string(str, charset, splited_str[i], &stream);
		i++;
	}
	splited_str[i] = 0;
	return (splited_str);
}
/*#include <stdio.h>
int main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	char	**splitted;
	splitted = ft_split(argv[1], argv[2]);
	int i = 0;
	while(splitted[i])
	{
		printf("%s\n", splitted[i]);
		i++;
	}
	return (0);
}*/
