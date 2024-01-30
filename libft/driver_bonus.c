/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <vlevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:42:00 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/25 17:36:12 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	long		count;
	int			i;

	if (!format)
		return (-1);
	va_start(ap, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += write(1, format, i);
			format = ft_identifier(&ap, format + i + 1, &count);
			i = 0;
		}
		else
			i++;
		if (count > 2147483647 || count == -1)
			break ;
	}
	count += write(1, format, i);
	va_end(ap);
	return (count);
}

const char	*ft_identifier(va_list *ap, const char *format, long *count)
{
	t_flags	flags;

	format = flag_check(format, &flags);
	if (*format == 'c')
		ft_char_handling(ap, count, &flags);
	else if (*format == 's')
		ft_str_handling(ap, count, &flags);
	else if (*format == 'i' || *format == 'd')
		ft_int_handling(ap, count, &flags);
	else if (*format == 'u')
		ft_unsgnd_int_handling(ap, count, &flags);
	else if (*format == 'x')
		ft_lchexa_handling(ap, count, &flags);
	else if (*format == 'p')
		ft_ptr_handling(ap, count, &flags);
	else if (*format == 'X')
		ft_uchhexa_handling(ap, count, &flags);
	else if (*format == '%')
		*count += write(1, "%", 1);
	return (format + 1);
}

void	init_flags(t_flags *flags)
{
	flags->f = 0;
	flags->sign = 0;
	flags->sharp = 0;
	flags->left_padding_space = 0;
	flags->left_padding_zero = 0;
	flags->right_padding = 0;
	flags->pad_sign = 0;
	flags->pad_side = -1;
	flags->pad_value = 0;
	flags->precision = 0;
	flags->precision_value = 0;
}

const char	*flag_check(const char *format, t_flags *flags)
{	
	init_flags(flags);
	while (*format)
	{
		if (*format == '#')
			flags->sharp = 1;
		else if (*format == '+')
			flags->sign = '+';
		else if (*format == ' ' && flags->sharp == -1)
			flags->sign = ' ';
		else if (*format == '-')
		{
			flags->pad_side = 1;
			flags->pad_sign = -32;
		}
		else if (*format == ' ')
			flags->sign = 32;
		else if (*format == '0' && flags->pad_sign != -32)
			flags->pad_sign = '0';
		else if (ft_isdigit(*format) || *format == '.')
			format = ft_pad_check(format, flags);
		else
			return (format);
		format++;
	}
	return (format);
}

const char	*ft_pad_check(const char *format, t_flags *flags)
{
	if (*format == '.')
	{
		flags->precision = 1;
		return (format);
	}
	if (flags->precision == 1)
		flags->precision_value = ft_atoi((char *)format);
	else
		flags->pad_value = ft_atoi((char *)format);
	while (ft_isdigit(*format))
		format++;
	return (format - 1);
}
