/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:00:58 by afocant           #+#    #+#             */
/*   Updated: 2024/07/16 18:52:41 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	else
		return (0);
}

static size_t	ft_count_strs(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (ft_is_sep(*s, c) && *s)
			s++;
		if (!ft_is_sep(*s, c) && *s)
		{
			count++;
			while (!ft_is_sep(*s, c) && *s)
				s++;
		}
	}
	return (count);
}

static size_t	ft_len_strsep(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (!ft_is_sep(*s, c) && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static char	**ft_fill_strs(const char *s, char c,
								char **split_s, size_t strs_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < strs_count)
	{
		while (ft_is_sep(*s, c) && *s)
			s++;
		if (!ft_is_sep(*s, c) && *s)
		{
			split_s[i] = ft_substr(s, 0, ft_len_strsep(s, c));
			if (!split_s[i])
			{
				j = 0;
				while (j < i)
					free(split_s[j++]);
				free(split_s);
				return (NULL);
			}
			i++;
			while (!ft_is_sep(*s, c) && *s)
				s++;
		}
	}
	return (split_s);
}

char	**ft_split(char const *s, char c)
{
	size_t	strs_count;
	char	**split_s;

	if (!s)
		return (NULL);
	strs_count = ft_count_strs(s, c);
	split_s = malloc((strs_count + 1) * sizeof(char *));
	if (!split_s)
		return (NULL);
	if (!ft_fill_strs(s, c, split_s, strs_count))
		return (NULL);
	split_s[strs_count] = 0;
	return (split_s);
}
