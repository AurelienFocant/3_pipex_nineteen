/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:20:39 by afocant           #+#    #+#             */
/*   Updated: 2024/06/05 13:24:14 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr_base(unsigned long long n, char *base)
{
	size_t	len_base;
	int		count;
	int		pre_count;

	count = 0;
	len_base = ft_getlen(base);
	if (n >= len_base)
	{
		pre_count = ft_print_ptr_base(n / len_base, base);
		if (pre_count < 0)
			return (-1);
		count += pre_count;
	}
	if (ft_print_char(base[n % len_base]) < 0)
		return (-1);
	count++;
	return (count);
}

int	ft_print_ptr(unsigned long long n)
{
	int	count;

	if (sizeof(n) != sizeof(void *))
		return (-1);
	count = ft_print_string("0x");
	if (count < 0)
		return (-1);
	count += ft_print_ptr_base(n, "0123456789abcdef");
	if (count < ft_getlen("0x"))
		return (-1);
	return (count);
}
