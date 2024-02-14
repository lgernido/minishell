/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printerr.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:09:32 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/05 12:09:32 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTERR_H
# define PRINTERR_H

# include "libft.h"

int	ft_printc(int c);
int	ft_printstr(char *str);
int	ft_printnb(int n);
int	ft_printp(void);
int	ft_format(va_list ap, const char format);
int	ft_printf_err(const char *format, ...);
int	ft_printhex(unsigned int nb, const char format);
int	ft_printhex(unsigned int nb, const char format);
int	ft_printui(unsigned int n);
#endif
