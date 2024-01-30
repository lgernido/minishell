/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lchexa_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <vlevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:20:34 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/25 17:39:52 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_flags(t_flags *flags, long nb)
{
	if (nb == 0)
		flags->sharp = 0;
	if (flags->sharp > 0)
		flags->sharp = 'x';
	if (nb == 0 && flags->precision > 0 && flags->precision_value == 0)
	{
		*flags->arg_str = 0;
		flags->pad_sign = 32;
	}
	return ;
}

void	ft_lchexa_handling(va_list *ap, long *count, t_flags *flags)
{
	char	*pad_str;
	char	*str;
	int		n;
	long	nb;

	nb = (unsigned int)va_arg(*ap, int);
	str = ft_itoa_base(nb, "0123456789abcdef");
	if (malloc_secure(str, count))
		return ;
	flags->arg_str = str;
	check_flags(flags, nb);
	n = def_padding(flags);
	pad_str = malloc((n + 1) * sizeof(char));
	if (malloc_secure(pad_str, count))
	{
		free(flags->arg_str);
		return ;
	}
	*count += write(1, fill_padding(pad_str, flags), n);
	free(flags->arg_str);
	free(pad_str);
	return ;
}
