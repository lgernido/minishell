/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_handling_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <vlevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:20:34 by vlevy             #+#    #+#             */
/*   Updated: 2023/12/01 19:05:09 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	define_size(t_flags *flags, long *count)
{
	int	n;

	if (flags->arg_str == NULL)
	{
		flags->arg_str = malloc(7 * sizeof(char));
		if (malloc_secure(flags->arg_str, count))
			return (1);
		ft_strlcpy(flags->arg_str, "(null)", 7);
		if (flags->precision)
		{
			if (flags->precision_value < 6)
				*flags->arg_str = 0;
			flags->precision_value = 0;
		}
	}
	else if (flags->precision)
	{
		n = ft_strlen(flags->arg_str);
		if (n > flags->precision_value)
			n = flags->precision_value;
		*(flags->arg_str + n) = 0;
		flags->precision_value = n;
	}
	return (0);
}

void	ft_str_handling(va_list *ap, long *count, t_flags *flags)
{
	char	*pad_str;
	int		n;

	flags->arg_str = ft_strdup(va_arg(*ap, char *));
	flags->sign = 0;
	if (define_size(flags, count))
		return ;
	n = def_padding(flags);
	pad_str = malloc((n + 1) * sizeof(char));
	if (malloc_secure(pad_str, count))
	{
		free(flags->arg_str);
		return ;
	}
	*count += write(1, fill_padding(pad_str, flags), n);
	free(pad_str);
	free(flags->arg_str);
	return ;
}
