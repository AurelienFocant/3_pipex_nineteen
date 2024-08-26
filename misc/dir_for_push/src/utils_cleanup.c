/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:59:13 by afocant           #+#    #+#             */
/*   Updated: 2024/08/27 01:05:56 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_wait_for_all_children(t_context *context)
{
	int	n;

	n = 0;
	while (n < context->nb_of_cmds)
	{
		wait(NULL);
		n++;
	}
}

void	ft_close_pipes(t_context *context)
{
	int	n;

	n = 0;
	while (n < (context->nb_of_pipes * 2))
	{
		close(context->pipes_fd[n]);
		n++;
	}
	free(context->pipes_fd);
}

void	ft_free_null(char *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	ft_free_null_strv(char **strv)
{
	size_t	i;

	i = 0;
	while (strv && strv[i])
		ft_free_null(strv[i++]);
	free(strv);
	strv = NULL;
}

int	ft_perror_exit(char *error, int my_errno, int errnb)
{
	if (!errno)
		errno = my_errno;
	perror(error);
	exit(errnb);
}
