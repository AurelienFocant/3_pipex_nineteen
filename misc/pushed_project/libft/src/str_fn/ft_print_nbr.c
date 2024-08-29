/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:10:34 by afocant           #+#    #+#             */
/*   Updated: 2024/06/04 20:10:39 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_neg_nbr(int n, char *base)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count = ft_print_string("-2147483648");
		if (count < 0)
			return (-1);
		return (count);
	}
	if (n < 0)
	{
		n = -n;
		if (ft_print_char('-') < 0)
			return (-1);
		count++;
	}
	count += ft_print_nbr_base(n, base);
	return (count);
}

int	ft_print_nbr_base(int n, char *base)
{
	size_t	len_base;
	int		count;
	int		pre_count;

	count = 0;
	if (n < 0)
		return (ft_print_neg_nbr(n, base));
	len_base = ft_getlen(base);
	if ((size_t) n >= len_base)
	{
		pre_count = ft_print_nbr_base(n / len_base, base);
		if (pre_count < 0)
			return (-1);
		count += pre_count;
	}
	if (ft_print_char(base[n % len_base]) < 0)
		return (-1);
	count++;
	return (count);
}

int	ft_print_unsigned_nbr_base(unsigned int n, char *base)
{
	size_t	len_base;
	int		count;
	int		pre_count;

	count = 0;
	len_base = ft_getlen(base);
	if (n >= len_base)
	{
		pre_count = ft_print_unsigned_nbr_base(n / len_base, base);
		if (pre_count < 0)
			return (-1);
		count += pre_count;
	}
	pre_count = ft_print_char(base[n % len_base]);
	if (pre_count < 0)
		return (-1);
	count += pre_count;
	return (count);
}
