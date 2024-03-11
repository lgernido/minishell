/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discard_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:38:47 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/11 10:17:47 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_correct_len(char *str)
{
	int	correct_string_size;
	int	i;

	i = 0;
	correct_string_size = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			i++;
			correct_string_size++;
		}
		else
			i++;
	}
	return (correct_string_size);
}

char	*ft_discard_quotes(char *str)
{
	char *correct_string;
	int correct_string_size;
	int i;

	i = 0;
	correct_string_size = ft_str_correct_len(str);
	correct_string = (char *)malloc(correct_string_size * sizeof(char) + 1);
	if (!correct_string)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			correct_string[i] = str[i];
			i++;
		}
		else
			i++;
	}
	correct_string[i] = '\0';
	return (correct_string);
}