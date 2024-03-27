/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:08:58 by purmerinos        #+#    #+#             */
/*   Updated: 2024/01/05 17:09:00 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_n_tab(char **tab, size_t tab_size)
{
	size_t	i;

	i = 0;
	while (i < tab_size)
	{
		if (tab[i] != NULL)
		{
			free(tab[i]);
		}
		++i;
	}
	free(tab);
	return ;
}
