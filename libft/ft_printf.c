/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:14:14 by lgernido          #+#    #+#             */
/*   Updated: 2023/11/23 09:53:43 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

int	ft_format(va_list ap, const char format)
{
	int	size;

	size = 0;
	if (format == 'c')
		size = ft_printc(va_arg(ap, int));
	if (format == 's')
		size = ft_printstr(va_arg(ap, char *));
	if (format == 'i' || format == 'd')
		size = ft_printnb(va_arg(ap, int));
	if (format == '%')
		size = ft_printp();
	if (format == 'u')
		size = ft_printui(va_arg(ap, unsigned int));
	if (format == 'x' || format == 'X')
		size = ft_printhex(va_arg(ap, unsigned int), format);
	if (format == 'p')
		size = ft_printptr(va_arg(ap, unsigned long), format);
	return (size);
}

int	ft_printf_err(const char *format, ...)
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
			size += ft_printc(format[i]);
		i++;
	}
	va_end(ap);
	return ((size));
}
