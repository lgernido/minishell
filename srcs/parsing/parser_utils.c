/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:15:17 by luciegernid       #+#    #+#             */
/*   Updated: 2024/02/12 10:25:15 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_samestr(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

/*
This is clean code ! ><
*/
int	ft_find_char_str(char c, char *str)
{
	if (ft_strchr(str, c) != NULL)
		return (1);
	else
		return (0);
}

/*
See if a position in s is escaped
if return odd -> escaped
if return even -> not escaped*/
int	ft_escape(char *s, int pos)
{
	int	count;

	count = 0;
	while (pos >= 0 && s[pos] == '\\')
	{
		count++;
		pos--;
	}
	return (count % 2);
}
/*
See if a position in s is between brackets
s = array in which to check for brackets
pos = position to check
*/
int	ft_quotes(char *s, int pos)
{
	int	double_quotes;
	int	single_quotes;
	int	i;

	double_quotes = 0;
	single_quotes = 0;
	i = 0;
	while (i <= pos)
	{
		if (s[i] == 34 && (i == 0 || !is_escaped(s, i - 1)) && single_quotes
			% 2 == 0)
			double_quotes++;
		if (s[i] == 39 && (i == 0 || single_quotes % 2 != 0 || !is_escaped(s, i
					- 1)) && double_quotes % 2 == 0)
			single_quotes++;
		i++;
	}
	if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
		return (1);
	return (0);
}
