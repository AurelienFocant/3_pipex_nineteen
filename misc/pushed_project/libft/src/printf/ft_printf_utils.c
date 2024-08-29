/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:48:25 by afocant           #+#    #+#             */
/*   Updated: 2024/05/02 16:51:33 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (1);
}

int	ft_print_string(char *s)
{
	int	count;

	if (!s)
		return (ft_print_string("(null)"));
	count = 0;
	while (*s)
	{
		if (write(1, s++, 1) < 0)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_getlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
