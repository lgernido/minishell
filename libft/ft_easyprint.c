/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_easyprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:48:17 by lgernido          #+#    #+#             */
/*   Updated: 2023/11/23 09:53:40 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

int	ft_printc(int c)
{
	write(2, &c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr_fd("(null)", 2);
		return (6);
	}
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printnb(int n)
{
	int		size;
	char	*nb;

	nb = ft_itoa(n);
	size = ft_printstr(nb);
	free(nb);
	return (size);
}

int	ft_printp(void)
{
	write(2, "%", 1);
	return (1);
}
