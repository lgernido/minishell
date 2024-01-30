/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_handling_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <vlevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:20:34 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/25 17:40:28 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ptr_handling_2(long *count, t_flags *flags, char *str,
	unsigned long long nb)
{
	int		n;
	char	*pad_str;

	n = def_padding(flags);
	pad_str = malloc(n + 1 * sizeof(char));
	if (malloc_secure(pad_str, count))
	{
		if (nb != 0)
			free (str);
		return ;
	}
	*count += write(1, fill_padding(pad_str, flags), n);
	free(pad_str);
	if (nb != 0)
		free(str);
}

void	ft_ptr_handling(va_list *ap, long *count, t_flags *flags)
{
	char				*str;
	unsigned long long	nb;

	nb = (unsigned long long)va_arg(*ap, void *);
	if (nb == 0)
		str = "(nil)";
	else
	{
		str = ft_itoa_ptr(nb, "0123456789abcdef");
		if (malloc_secure(str, count))
			return ;
		flags->sharp = 'x';
	}
	flags->arg_str = str;
	ptr_handling_2(count, flags, str, nb);
	return ;
}
