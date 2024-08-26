/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:21:20 by afocant           #+#    #+#             */
/*   Updated: 2024/07/23 23:31:15 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	n;
	int		neg_flag;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	neg_flag = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		neg_flag = -1;
		str++;
	}
	n = 0;
	while (ft_isdigit(*str))
		n = (n * 10) + (*str++ - '0');
	return (n * neg_flag);
}
