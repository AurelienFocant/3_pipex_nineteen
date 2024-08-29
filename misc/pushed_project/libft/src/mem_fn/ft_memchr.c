/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:54:29 by afocant           #+#    #+#             */
/*   Updated: 2024/04/17 20:54:30 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *) s;
	i = 0;
	while (n--)
	{
		if (str[i] == (unsigned char) c)
			return ((void *) s + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int main()
{
	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
    	printf("%s", (char *)ft_memchr(tab, 49, 7));
}
*/
