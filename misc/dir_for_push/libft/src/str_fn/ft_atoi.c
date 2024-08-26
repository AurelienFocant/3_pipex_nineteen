/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:47:25 by afocant           #+#    #+#             */
/*   Updated: 2024/08/21 16:59:55 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_a_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	neg_flag;

	while (ft_is_a_space(*str))
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
