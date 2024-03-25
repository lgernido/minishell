/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:31:19 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/22 12:03:20 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

char	*fetch_input(int error_code)
{
	char	*user_input;

	if (error_code == 0)
		write(1, "👌", 4);
	else
		write(2, "😵", 4);
	user_input = readline(" minishell> ");
	add_history(user_input);
	return (user_input);
}

int	main(int ac, char **av, char **envp)
{
	t_core	core;

	((void)ac, (void)av);
	if (isatty(0) != 1)
	{
		ft_printf_err("Nope.\n");
		return (0);
	}
	init_sig();
	ft_bzero(&core, sizeof(t_core));
	handle_envp(envp, &core);
	update_shell_lvl(&core);
	while (1)
	{
		minishell_driver(&core);
	}
}
