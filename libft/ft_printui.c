/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:09:16 by lgernido          #+#    #+#             */
/*   Updated: 2023/11/23 09:52:11 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printerr.h"

int	ft_nbsize(unsigned int n)
{
	int	size;

	size = 0;
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_uitoa(unsigned int n)
{
	char	*nb;
	int		size;

	size = ft_nbsize(n);
	nb = malloc(sizeof(char) * (size + 1));
	if (!nb)
		return (0);
	nb[size] = '\0';
	while (n != 0)
	{
		nb[size - 1] = n % 10 + '0';
		n /= 10;
		size--;
	}
	return (nb);
}

int	ft_printui(unsigned int n)
{
	int		size;
	char	*nb;

	size = 0;
	if (n == 0)
	{
		write(2, "0", 1);
		size = 1;
	}
	else
	{
		nb = ft_uitoa(n);
		size = ft_printstr(nb);
		free(nb);
	}
	return (size);
}
