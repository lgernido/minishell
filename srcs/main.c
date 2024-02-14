/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciegernidos <luciegernidos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:31:19 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/11 13:39:22 by luciegernid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "AST.h"
#include <readline/readline.h>
#include <unistd.h>

atomic_int	g_signal = 0;

static void	check_for_empty(t_core *core, char *str)
{
	if (!str)
	{
		printf("exit\n");
		ft_clean_exit(core, 0);
	}
}

static void	wait_input(t_core *core)
{
	char	*str;

	while (1)
	{
		if (g_signal)
			react_sig(core);
		if (!core->error_code)
			write(1, "👌", 4);
		else
			write(2, "😵", 4);
		str = readline(" minishell>");
		check_for_empty(core, str);
		add_history(str);
		// split_str(core, str);
		// ft_tokenizer(str);
		/*Input parsing fonction here,
			w/ list and str as argument. STR need to be free in the parsing !!*/
		// free(str);
		free(str);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_core	core;

	((void)ac, (void)av);
	init_sig();
	init_core(&core);
	parse_envp(envp, &core);
	update_shell_lvl(&core);
	ft_env(NULL, &core);
	wait_input(&core);
}
