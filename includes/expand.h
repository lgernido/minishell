/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:35:46 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/18 12:35:47 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H

# define EXPAND_H

# include "minishell.h"

void	init_vector(t_core *core);
char	*get_rid_of_double_quote(char *str);
t_bool	is_a_relevant_quote(int c, int flag);
void	update_current_quote(int *current_quote, int quote);
void	create_new_sub_token(t_core *core, char *new_token_start,
			char *new_token_end, t_subtypes type);
char	*ft_strndup(char *start, char *end);
void	update_iterator_position(t_core *core);
char	*expand_var_init(t_core *core, char *str);

#endif
