/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:27:39 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/13 15:48:21 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = NULL;
	if (nmemb == 0 || size == 0)
	{
		p = malloc(1 * sizeof (char));
		return (p);
	}
	if ((nmemb * size) % nmemb != 0)
		return (NULL);
	p = malloc(nmemb * size);
	if (p != NULL)
		ft_bzero(p, nmemb * size);
	return (p);
}

/*int	main(void)
{
	int	*p;

	p = calloc(0, sizeof(int));
	free(p);
	return (0);
}*/
