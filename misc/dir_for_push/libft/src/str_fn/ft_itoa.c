/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:50:36 by afocant           #+#    #+#             */
/*   Updated: 2024/07/19 14:55:36 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_findlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len = 1;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static unsigned int	ft_is_negative(int n)
{
	if (n < 0)
		return ((unsigned int) -n);
	else
		return ((unsigned int) n);
}

char	*ft_itoa(int n)
{
	unsigned int	unsigned_n;
	char			*nbr;
	int				len;

	len = ft_findlen(n);
	unsigned_n = ft_is_negative(n);
	nbr = malloc((len + 1) * sizeof(char));
	if (nbr == NULL)
		return (NULL);
	if (n == 0)
		nbr[0] = '0';
	if (n < 0)
		nbr[0] = '-';
	nbr[len] = '\0';
	while (unsigned_n)
	{
		nbr[--len] = (unsigned_n % 10) + '0';
		unsigned_n /= 10;
	}
	return (nbr);
}
