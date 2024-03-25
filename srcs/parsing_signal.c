/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:54:01 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/25 17:54:01 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_handler(int sig)
{
	g_signal = 130;
	(void)sig;
	write(1, "\n", 1);
	return ;
}

void	parsing_sig(void)
{
	struct sigaction	act;

	signal(SIGQUIT, SIG_IGN);
	ft_bzero(&act, sizeof(act));
	act.sa_handler = parsing_handler;
	sigaction(SIGINT, &act, NULL);
}
