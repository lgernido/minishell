/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:49 by luciegernid       #+#    #+#             */
/*   Updated: 2024/03/06 10:54:15 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_ascii(char *str)
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

static int	ft_dprintf(int fd, const char *format, ...)
{
	int		i;
	int		size;
	va_list	ap;

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

void	ft_start_parse(t_core *minishell, char *str)
{
	char	*token;

	if (ft_is_ascii(str))
	{
		ft_dprintf(2, "minishell: invalid ascii characters found in string\n");
		return ;
	}
	if (ft_quotes(str))
	{
		ft_dprintf(2, "unclosed quotes can't be interpreted\n");
		return ;
	}
	ft_split_tokens(minishell, str);
	token = ft_tokenizer(minishell);
	if (token)
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n",
			token);
		ft_clear_token_list(&minishell->token_list, free);
		return ;
	}
}
