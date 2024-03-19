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

void	parse_word_init(t_core *core, char *token_string);
int		init_vector(t_core *core);
char	*get_rid_of_double_quote(char *str);
t_bool	is_a_relevant_quote(int c, int flag);
void	update_current_quote(int *current_quote, int quote);
int		create_new_sub_token(t_core *core, char *new_token_start,
			char *new_token_end, t_subtypes type);
char	*ft_strndup(char *start, char *end);
int		update_iterator_position(t_core *core);
char	*expand_var_init(t_core *core, char *str);
char	*join_vector_in_a_string(t_core *core);
void	remove_quotes_and_highlight_wildcards(t_core *core);
void	check_for_mem_error(t_core *core, char **str_to_check,
			char **str_to_free);
t_bool	sub_token_need_expand(t_sub_token *sub_token);
void	expand_sub_token(t_core *core, int i);

#endif
