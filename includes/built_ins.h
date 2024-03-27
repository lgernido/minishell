/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:47:15 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/08 19:47:15 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H

# define BUILT_INS_H

# include "minishell.h"

// For ft_pwd
# define PWD_BUFFER 128
# define BUFFER_LIMIT 4096
// Error Code

// ========================================================================= //

// utils for bult_in in built_in_utils.c
int				get_number_of_args(char **av);
// check if the var has been unset
t_bool			is_set(char *str);
// used to update var
char			**get_valid_addr(t_core *core, char *av);

// Used by export
t_bool			is_the_var(char *var, char *env);
void			print_export(t_core *core);

// Used to retrieve a var from env. var should include '$'
// --> char *str = ft_getenv(core, "$PATH"). return str should be fried
char			*ft_getenv(t_core *core, char *var);
// ========================================================================= //

// built-ins
int				ft_echo(char **av, t_core *core); // echo.c
int				ft_cd(char **av, t_core *core); // cd.c
int				ft_exit(char **av, t_core *core); // exit.c
int				ft_pwd(char **av, t_core *core); // unset.c
int				ft_env(char **av, t_core *core); // env.c
int				ft_unset(char **av, t_core *core); // unset.c
int				ft_export(char **av, t_core *core); //export.c

// built_in_utils.c

// deduce argument count from argument vector
int				get_number_of_args(char **av);

// Used to retrieve a var from env. var should include '$'
// --> char *str = ft_getenv(core, "$PATH"). return str should be fried
char			*ft_getenv(t_core *core, char *var);

// return TRUE if str != NULL
t_bool			is_set(char *str);

// ========================================================================= //

// cd_error_mangement.c
int				throw_error_message(void *arg, void (*message)(void *));
void			too_many_args(void *arg);
void			home_not_set(void *arg);
void			error_while_shifting_directory(void *path);

// ========================================================================= //

// swap_var.c 
// take as parameter the name of the bar and the new content, and will handle
// to rewrite it. Will set a new entry if the variable isn't referenced yet.
void			swap_var(t_core *core, char *var_content, const char *var_name);

// free the buffer if it is not NULL
void			free_if_needed(char **str);

// ========================================================================= //

// get_env_adress.c
// will return the adress of the var to modify, or a new writable address
// if the variable doesn't exist yet

char			**get_valid_addr(t_core *core, char *av);

// ========================================================================= //

// pwd_utils.c

// fill the buffer with pwd, reallocating it if needed without exceed
// a define limit (see BUFFER_LIMIT define)
char			*get_pwd_in_buffer(t_core *core);

// ========================================================================= //

// cd_update_env_var.c

// is called by ft_cd to refresh $PWD and $OLDPWD in env
void			update_env_var(t_core	*core, char *old_pwd);

// ========================================================================= //

// parse_export_var.c
// used by export to check wether the variable match requirements
int				parse_before_equal_sign(char *str);

// ========================================================================= //

// export_check_forbidden_var.c
// those two functions protect fro; overwriting the "_=" var
int				check_len(char *str);
int				is_the_var_write_protected(char	*str);
#endif
