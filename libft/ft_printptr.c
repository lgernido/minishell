/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:33:13 by lgernido          #+#    #+#             */
/*   Updated: 2023/11/23 09:53:48 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

int	ft_ptrsize(unsigned long nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

void	ft_writeptr(unsigned long nb, const char format)
{
	if (nb >= 16)
	{
		ft_writeptr(nb / 16, format);
		ft_writeptr(nb % 16, format);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_fd(nb + '0', 2);
		else
			ft_putchar_fd(nb - 10 + 'a', 2);
	}
}

int	ft_printptr(unsigned long nb, const char format)
{
	int	size;

	size = 0;
	if (!nb)
		return (ft_printstr("(nil)"));
	ft_putstr_fd("0x", 2);
	size += 2;
	ft_writeptr(nb, format);
	size += ft_ptrsize(nb);
	return (size);
}
