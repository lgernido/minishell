/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:50:49 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/05 10:05:29 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
i = character's position in the array
str = array to analyze
sep = separator
sign = handling context
	0 -> check if c[i] and c[i - 1] == sep
	1 -> check if c[i] == sep and c[i + 1] != sep
	2 -> same as 0 but with c[i + 1]
	3 -> check if c[i] == sep
*/

int	ft_split_utils(int i, char *str, char *sep, int sign)
{
	if (sign == 1 && ft_find_char_str(str[i], sep) && !ft_find_char_str(str[i
			+ 1], sep) && !ft_quotes(str, i) && !ft_escape(str, i - 1))
		return (1);
	else if (sign == 0 && ft_find_char_str(str[i], sep) && i > 0
		&& ft_find_char_str(str[i - 1], sep) && !ft_quotes(str, i)
		&& !ft_escape(str, i - 1))
		return (1);
	else if (sign == 2 && ft_find_char_str(str[i], sep) && i > 0
		&& ft_find_char_str(str[i - 1], sep) && !ft_quotes(str, i)
		&& !ft_escape(str, i - 1))
		return (1);
	else if (sign == 3 && ft_find_char_str(str[i], sep) && !ft_quotes(str, i)
		&& !ft_escape(str, i - 1))
		return (1);
	return (0);
}

int	ft_split_tokens2(t_core *minishell, char *str, int *i, t_token **start)
{
	if (!ft_find_char_str(str[*i], " \t") && !ft_quotes(str, *i)
		&& !ft_escape(str, *i - 1))
	{
		ft_add_token_list(start, ft_create_token(minishell, *i, str));
		(*i)++;
		return (0);
	}
	if ((ft_find_char_str(str[*i], "|;<>&()") && *i > 0
			&& !ft_find_char_str(str[*i - 1], "|;<>&()")) && !ft_quotes(str, *i)
		&& !ft_escape(str, *i - 1))
		ft_add_token_list(start, ft_create_token(minishell, *i, str));
	return (1);
}
void	ft_split_tokens(t_core *minishell, char *str)
{
	int		i;
	t_token	**start;
	int		token_start;

	i = 0;
	start = &minishell->token_list;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			i++;
			continue ;
		}
		if (ft_find_char_str(str[i], "|;<>&()"))
		{
			ft_add_token_list(start, ft_create_token(minishell, i, str));
			i++;
		}
		else
		{
			token_start = i;
			while (str[i] && !ft_find_char_str(str[i], " \t|;<>&()"))
				i++;
			ft_add_token_list(start, ft_create_token(minishell, token_start,
					str));
		}
	}
	ft_add_token_list(start, ft_create_arg_token(minishell, "newline",
			T_NEWLINE));
}

// void	ft_split_tokens(t_core *minishell, char *str)
// {
// 	int		i;
// 	t_token	**start;

// 	i = 0;
// 	start = &minishell->token_list;
// 	while (str[i])
// 	{
// 		if (!ft_split_tokens2(minishell, str, &i, start))
// 			continue ;
// 		if (ft_find_char_str(str[i], " \t"))
// 		{
// 			i++;
// 			continue ;
// 		}
// 		if (ft_split_utils(i, str, "|", 1) || ft_split_utils(i, str, "|", 0)
// 			|| ft_split_utils(i, str, ">", 1) || ft_split_utils(i, str, ">", 0)
// 			|| ft_split_utils(i, str, "<", 1) || ft_split_utils(i, str, "<", 0)
// 			|| ft_split_utils(i, str, "&", 2) || ft_split_utils(i, str, ";()",
// 				3))
// 			ft_add_token_list(start, ft_create_token(minishell, i, str));
// 		i++;
// 	}
// 	if (i > 0)
// 	{
// 		ft_add_token_list(&minishell->token_list, ft_create_token(minishell, i,
// 				str));
// 		ft_add_token_list(&minishell->token_list, ft_create_arg_token(minishell,
// 				"newline", T_NEWLINE));
// 	}
// }
