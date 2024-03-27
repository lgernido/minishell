/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:15:17 by luciegernid       #+#    #+#             */
/*   Updated: 2024/03/22 15:51:44 by lgernido         ###   ########.fr       */
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
	if (*str)
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
	return (c == ' ' || c == '\t' || c == '\'' || c == '\"'
		|| c == ')' || c == '(' || c == '>' || c == '<');
}

int	count_parenthesis(char *str)
{
	int		flag;
	int		parenthesis_counter;
	size_t	i;

	i = 0;
	flag = 0;
	parenthesis_counter = 0;
	while (str[i] != '\0' && parenthesis_counter != -1)
	{
		if (str[i] == '\'' || str[i] == '"')
			update_flag(&flag, str[i]);
		else if (flag == 0 && str[i] == '(')
			++parenthesis_counter;
		else if (flag == 0 && str[i] == ')')
			--parenthesis_counter;
		++i;
	}
	if (parenthesis_counter != 0)
		return (-1);
	return (0);
}
