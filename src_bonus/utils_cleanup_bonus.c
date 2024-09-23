/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleanup_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:43:54 by afocant           #+#    #+#             */
/*   Updated: 2024/09/23 13:18:23 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_print_error(char *error_msg, char *str_error)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*str;

	tmp1 = ft_strjoin("pipex: ", error_msg);
	tmp2 = ft_strjoin(tmp1, ": ");
	tmp3 = ft_strjoin(tmp2, str_error);
	str = ft_strjoin(tmp3, "\n");
	if (!tmp1 || !tmp2 || !tmp3 || !str)
		ft_putstr_fd("error writing error msg\n", STDERR_FILENO);
	else
		ft_putstr_fd(str, STDERR_FILENO);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(str);
}

int	ft_cmd_perror(char *error_msg, int my_errno, int exitcode)
{
	if (!errno)
		errno = my_errno;
	if (errno == EACCES)
		ft_print_error(error_msg, "permission denied");
	else if (errno == ENOENT)
		ft_print_error(error_msg, "command not found");
	else
		ft_print_error(error_msg, strerror(errno));
	exit(exitcode);
}

int	ft_perror_exit(char *error, int my_errno, int errnb)
{
	if (!errno)
		errno = my_errno;
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	perror(error);
	exit(errnb);
}

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
