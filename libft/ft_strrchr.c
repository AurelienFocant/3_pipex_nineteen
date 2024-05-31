/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:06:50 by afocant           #+#    #+#             */
/*   Updated: 2024/04/23 14:23:54 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*t;

	len = ft_strlen(s);
	t = (char *)(s + len);
	while (*t != (char) c)
		if (--t == (s - 1))
			return (NULL);
	return (t);
}
