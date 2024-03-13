/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:48:51 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/13 15:18:29 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_ascii(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0 || str[i] > 127)
			return (1);
		i++;
	}
	return (0);
}
int	ft_handle_backslash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}

int	ft_handle_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '(' || str[i + 1] == '{'))
			return (1);
		i++;
	}
	return (0);
}

void	ft_discard_quotes(t_core *minishell)
{
	t_token	*tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		tmp->value = ft_strtrim(tmp->value, "\"");
		tmp->value = ft_strtrim(tmp->value, "\'");
		tmp = tmp->next;
	}
	return ;
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int i;
	int size;
	va_list ap;

	i = 0;
	size = 0;
	if (format == NULL)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			size += ft_format(ap, format[i + 1]);
			i++;
		}
		else
			size += write(fd, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (size);
}