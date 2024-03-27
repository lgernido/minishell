/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:20:35 by purmerinos        #+#    #+#             */
/*   Updated: 2024/03/25 16:20:35 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_open_parenthesis(t_token_stream_node *stream) {
  if (stream->prev == NULL) {
    return (1);
  }
  if (stream->prev->type != T_PAR_OPEN && stream->prev->type != T_AND &&
      stream->prev->type != T_OR) {
    return (1);
  }
  if (stream->next->type == T_PIPE || stream->next->type == T_AND ||
      stream->next->type == T_OR || stream->next->type == T_PAR_CLOSE) {
    return (1);
  }
  return (0);
}

int check_close_parenthesis(t_token_stream_node *stream) {
  if (stream->prev->type != T_PAR_CLOSE &&
      stream->prev->type != T_SIMPLE_QUOTES &&
      stream->prev->type != T_DOUBLE_QUOTES && stream->prev->type != T_WORD) {
    return (1);
  }
  if (stream->next->type != T_PAR_CLOSE && stream->next->type != T_AND &&
      stream->next->type != T_OR && stream->next->type != T_NEWLINE) {
    return (1);
  }
  return (0);
}
