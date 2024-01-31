/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_padding_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <vlevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:57:25 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/25 17:35:37 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*char_padding(char *pad_str, t_flags *flags, long *count)
{
	char	*tmp;

	tmp = pad_str;
	while (flags->left_padding_space--)
		*count += write(1, " ", 1);
	if (flags->sharp > 0)
	{
		*tmp++ = '0';
		*tmp++ = flags->sharp;
	}
	if (flags->sign > 0)
		*tmp++ = flags->sign;
	while (flags->left_padding_zero--)
		*count += write(1, "0", 1);
	while (flags->precision_value--)
		*count += write(1, "0", 1);
	*count += write(1, flags->arg_str, 1);
	while (flags->right_padding--)
		*count += write(1, " ", 1);
	*tmp = 0;
	return (pad_str);
}
