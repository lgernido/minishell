/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:15:17 by luciegernid       #+#    #+#             */
/*   Updated: 2024/03/14 09:54:16 by lgernido         ###   ########.fr       */
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

void	ft_strdel(char **str)
{
	free(*str);
	*str = NULL;
}

int	ft_find_char_str(char c, char *str)
{
	if (ft_strchr(str, c) != NULL)
		return (1);
	else
		return (0);
}

t_bool	ft_is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == ';');
}

int	ft_quotes(char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			double_quotes++;
		else if (str[i] == '\'')
			single_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (1);
	else
		return (0);
}
