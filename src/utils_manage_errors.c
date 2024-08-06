/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_manage_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:59:17 by afocant           #+#    #+#             */
/*   Updated: 2024/07/06 00:59:21 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_null(char *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	ft_free_null_strv(char **strv)
{
	size_t	i;

	i = 0;
	while (strv[i])
		ft_free_null(strv[i++]);
	free(strv);
	strv = NULL;
}

int		ft_perror_exit(char *error, int my_errno, int errnb)
{
	/*	should free stuff
	*	and close pipes !
	*	here or ft_finish_early, smth like this
	*/ 
	if (!errno)
		errno = my_errno;
	perror(error);
	exit(errnb);
}
