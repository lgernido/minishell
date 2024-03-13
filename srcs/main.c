/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:31:19 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/16 15:30:29 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "minishell.h"
#include "printerr.h"
#include <readline/readline.h>
#include <unistd.h>

atomic_int	g_signal = 0;

// static void	check_for_empty(t_core *core, char *str)
// {
// 	if (!str)
// 	{
// 		printf("exit\n");
// 		ft_clean_exit(core, 0);
// 	}
// }

char	*fetch_input(int error_code)
{
	char	*user_input;
	// t_token	*tmp;

	if (error_code == 0)
		write(1, "👌", 4);
	else
		write(2, "😵", 4);
	user_input = readline(" minishell>");
	add_history(user_input);
	return (user_input);
	// ft_tokenizer(str);
	// // split_str(core, str);
	// ft_split_tokens(core, str);
	// tmp = core->token_list;
	// while (tmp)
	// {
	// 	printf("token value :%s\n", tmp->value);
	// 	printf("token type :%d\n", tmp->type);
	// 	tmp = tmp->next;
	// }
	/*Input parsing fonction here,
		w/ list and str as argument. STR need to be free in the parsing !!*/
	// free(str);
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
	init_core(&core);
	parse_envp(envp, &core);
	update_shell_lvl(&core);
	while (1)
	{
		minishell_driver(&core);
	}
}
