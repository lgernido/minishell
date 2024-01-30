/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handling_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <vlevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:20:34 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/25 17:35:14 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_char_handling(va_list *ap, long *count, t_flags *flags)
{
	char	*pad_str;
	char	c;
	int		n;

	flags->arg_str = ft_calloc(2, sizeof(char));
	if (malloc_secure(flags->arg_str, count))
		return ;
	c = va_arg(*ap, int);
	if (c == 0)
		flags->pad_value -= 1;
	*(flags->arg_str) = c;
	n = def_padding(flags);
	pad_str = malloc((n + 1) * sizeof(char));
	if (malloc_secure(pad_str, count))
	{
		free(flags->arg_str);
		return ;
	}
	if (c == 0)
		char_padding(pad_str, flags, count);
	else
		*count += write(1, fill_padding(pad_str, flags), n);
	free(flags->arg_str);
	free(pad_str);
	return ;
}
