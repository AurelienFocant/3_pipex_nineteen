/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:23:17 by afocant           #+#    #+#             */
/*   Updated: 2024/07/26 16:19:17 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_and_null(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_extract_line(char *stash)
{
	size_t	len;
	char	*line;
	int		i;

	if (!stash)
		return (NULL);
	len = 0;
	while (stash[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1 + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_trim_stash(char *stash, char *start)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = ft_strlen(start);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (ft_free_and_null(&stash));
	i = 0;
	while (i < len)
		res[i++] = *start++;
	res[i] = '\0';
	if (!*res)
		ft_free_and_null(&res);
	ft_free_and_null(&stash);
	return (res);
}
