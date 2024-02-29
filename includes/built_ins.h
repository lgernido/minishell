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
void			print_export(char **env);

// Used to retrieve a var from env. var should include '$'
// --> char *str = ft_getenv(core, "$PATH"). return str should be fried
char			*ft_getenv(t_core *core, char *var);
// ========================================================================= //

// built-ins
int				echo(char **av, t_core *core); // echo.c
int				ft_cd(char **av, t_core *core); // cd.c
int				ft_exit(char **av, t_core *core); // exit.c
int				ft_pwd(char **av, t_core *core);
int				ft_env(char **av, t_core *core); // env.c
int				ft_unset(char **av, t_core *core); // unset.c
int				ft_export(char **av, t_core *core); //export.c

// ========================================================================= //
// cd_utils.c && cd_update_env_var.c
void			too_many_args(void *arg);
char			*assign_pwd(t_core *core);
void			update_env_var(t_core	*core, char *old_pwd);
void			home_not_set(void *arg);
void			swap_var(t_core *core, char *var_content, const char *var_name);
void			error_while_shifting_directory(void *path);
int				go_specified_dir(void	*path);
int				throw_error_message(void *arg, void (*message)(void *));
char			*get_pwd_in_buffer(void);
char			*get_pwd(char *buffer, int len);

#endif
