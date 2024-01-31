/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_padding_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <vlevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:57:25 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/25 17:36:24 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_padding(char *pad_str, t_flags *flags)
{
	char	*tmp;

	tmp = pad_str;
	while (flags->left_padding_space--)
		*tmp++ = ' ';
	if (flags->sharp > 0)
	{
		*tmp++ = '0';
		*tmp++ = flags->sharp;
	}
	if (flags->sign > 0)
		*tmp++ = flags->sign;
	while (flags->left_padding_zero--)
		*tmp++ = '0';
	while (flags->precision_value--)
		*tmp++ = '0';
	ft_strlcpy(tmp, flags->arg_str, ft_strlen(flags->arg_str) + 1);
	while (*tmp)
		tmp++;
	while (flags->right_padding--)
		*tmp++ = ' ';
	*tmp = 0;
	return (pad_str);
}
