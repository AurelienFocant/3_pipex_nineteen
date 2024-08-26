/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:46:28 by afocant           #+#    #+#             */
/*   Updated: 2024/06/05 13:41:33 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int	ft_print_char(char c);
int	ft_print_string(char *s);
int	ft_getlen(char *s);

int	ft_print_nbr_base(int n, char *base);
int	ft_print_neg_nbr_base(int n, char *base);
int	ft_print_unsigned_nbr_base(unsigned int n, char *base);

int	ft_print_ptr_base(unsigned long long n, char *base);
int	ft_print_ptr(unsigned long long n);

int	ft_parse_arg(char c, va_list *arg);
int	ft_printf(const char *format, ...);

#endif
