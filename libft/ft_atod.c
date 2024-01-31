/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.f                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:02:17 by purmerinos        #+#    #+#             */
/*   Updated: 2024/01/06 15:02:19 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(char *str)
{
	int		whole_part;
	double	decimal_part;
	int		sign;

	sign = 1;
	if (*str == '-')
		sign *= -1;
	whole_part = ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		str++;
	decimal_part = ft_atoi(str);
	while (decimal_part > 1.)
		decimal_part *= 0.1;
	if (sign < 0)
		decimal_part *= -1;
	return (whole_part + decimal_part);
}
