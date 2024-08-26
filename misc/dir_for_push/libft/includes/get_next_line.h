/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:41:18 by afocant           #+#    #+#             */
/*   Updated: 2024/08/21 16:59:10 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 256
# endif

# include "get_next_line.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/resource.h>
# include <limits.h>

char	*ft_get_next_line(int fd);
char	*ft_read_file(int fd, char **stash);
char	*ft_join_stash_buff(char *stash, char *buf, size_t buf_len);
char	*ft_divide_stash(char **stash);

char	*ft_free_and_null(char **str);
char	*ft_extract_line(char *stash);
char	*ft_trim_stash(char *stash, char *start);

#endif
