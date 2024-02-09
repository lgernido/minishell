/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:09:07 by lgernido          #+#    #+#             */
/*   Updated: 2023/11/23 09:53:46 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

int	ft_hexasize(unsigned int nb)
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

void	ft_writehex(unsigned int nb, const char format)
{
	if (nb >= 16)
	{
		ft_writehex(nb / 16, format);
		ft_writehex(nb % 16, format);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_fd(nb + '0', 2);
		else
		{
			if (format == 'x')
				ft_putchar_fd(nb - 10 + 'a', 2);
			if (format == 'X')
				ft_putchar_fd(nb - 10 + 'A', 2);
		}
	}
}

int	ft_printhex(unsigned int nb, const char format)
{
	if (nb == 0)
	{
		write(2, "0", 1);
		return (1);
	}
	else
		ft_writehex(nb, format);
	return (ft_hexasize(nb));
}
