/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_padding_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <vlevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:46:50 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/25 17:35:56 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	def_padding(t_flags *flags)
{
	if (flags->sharp > 0)
		flags->f += 2;
	if (flags->sign > 0)
		flags->f += 1;
	flags->precision_value -= ft_strlen(flags->arg_str);
	if (flags->precision_value <= 0)
		flags->precision_value = 0;
	flags->left_padding_space = flags->pad_value - flags->f
		- flags->precision_value - ft_strlen(flags->arg_str);
	if (flags->left_padding_space <= 0)
		flags->left_padding_space = 0;
	if (flags->pad_sign == '0' && flags->precision <= 0)
	{
		flags->left_padding_zero = flags->left_padding_space;
		flags->left_padding_space = 0;
	}
	if (flags->pad_side == 1)
	{
		flags->right_padding = flags->left_padding_space;
		flags->pad_sign = 32;
		flags->left_padding_space = 0;
	}
	return (flags->left_padding_space + flags->left_padding_zero
		+ flags->right_padding + flags->precision_value
		+ ft_strlen(flags->arg_str) + flags->f);
}
