/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:44:16 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/03 16:44:17 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	sig_handler(int sig)
{
	g_signal = 1;
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	write(2, "😵", 4);
	rl_redisplay();
}

void	init_sig(void)
{
	struct sigaction	act;

	signal(SIGQUIT, SIG_IGN);
	ft_bzero(&act, sizeof(act));
	act.sa_handler = sig_handler;
	sigaction(SIGINT, &act, NULL);
}

void	react_sig(t_core *core)
{
	core->error_code = 130;
	g_signal = 0;
}
