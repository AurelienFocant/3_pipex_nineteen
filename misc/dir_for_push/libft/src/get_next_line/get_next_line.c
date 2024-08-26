/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:02:57 by afocant           #+#    #+#             */
/*   Updated: 2024/07/29 15:04:36 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_divide_stash(char **stash)
{
	char	*nl;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	nl = ft_strchr(*stash, '\n');
	if (!nl)
		return (NULL);
	line = ft_extract_line(*stash);
	if (!line)
		return (ft_free_and_null(stash));
	*stash = ft_trim_stash(*stash, ++nl);
	return (line);
}

char	*ft_join_stash_buff(char *stash, char *buf, size_t buf_len)
{
	size_t	stash_len;
	size_t	i;
	size_t	j;
	char	*res;

	if (!stash)
		stash_len = 0;
	else
		stash_len = ft_strlen(stash);
	res = malloc(sizeof(char) * stash_len + buf_len + 1);
	if (!res)
		return (ft_free_and_null(&stash));
	j = 0;
	i = 0;
	while (i < stash_len)
		res[j++] = stash[i++];
	i = 0;
	while (i < buf_len)
		res[j++] = buf[i++];
	res[j] = '\0';
	free(stash);
	return (res);
}

char	*ft_read_file(int fd, char **stash)
{
	char	buffer[BUFFER_SIZE];
	char	*line;
	int		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (ft_free_and_null(stash));
	while (bytes_read)
	{
		*stash = ft_join_stash_buff(*stash, buffer, (size_t) bytes_read);
		line = ft_divide_stash(stash);
		if (line)
			return (line);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (stash && *stash)
	{
		line = *stash;
		*stash = NULL;
		return (line);
	}
	else
		return (ft_free_and_null(stash));
}

char	*ft_get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*line;

	if (fd == -1 || fd >= FD_MAX || fd >= _POSIX_OPEN_MAX)
		return (NULL);
	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (ft_free_and_null(&stash[fd]));
	line = ft_divide_stash(&stash[fd]);
	if (line)
		return (line);
	line = ft_read_file(fd, &stash[fd]);
	if (line)
		return (line);
	return (NULL);
}
