/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:38:50 by afocant           #+#    #+#             */
/*   Updated: 2024/09/23 14:41:34 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_execute_child(t_context *context)
{
	execve(context->executable, context->cmd, context->envp);
	ft_free_null((void **) &(context->executable));
	ft_free_null_strv(&(context->path));
	ft_free_null_strv(&(context->cmd));
	ft_perror_exit("Execve has failed", errno, 12);
}

void	ft_prepare_pipe(t_context *context)
{
	int	n;

	context->pipes_fd = malloc(sizeof(int) * (context->nb_of_pipes * 2));
	if (context->pipes_fd == NULL)
		ft_perror_exit("Malloc on pipe array has failed", errno, 4);
	n = 0;
	while (n < context->nb_of_pipes * 2)
	{
		if (pipe(context->pipes_fd + n) == -1)
			ft_perror_exit("Pipe creation has failed", errno, 5);
		n += 2;
	}
}

pid_t	sys_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_perror_exit("Fork failed", errno, 6);
	return (pid);
}

void	ft_pipex(t_context *context)
{
	int		curr_cmd_nb;
	pid_t	pid;

	ft_prepare_heredoc(context);
	ft_prepare_pipe(context);
	curr_cmd_nb = 0;
	while (curr_cmd_nb < context->nb_of_cmds)
	{
		pid = sys_fork();
		if (pid == CHILD)
		{
			errno = EXIT_SUCCESS;
			context->curr_cmd_nb = curr_cmd_nb;
			ft_setup_redirection(context);
			ft_close_pipes(context);
			ft_find_executable(context);
			ft_execute_child(context);
		}
		curr_cmd_nb++;
	}
	ft_close_pipes(context);
	ft_wait_for_all_children(context);
	ft_free_null_strv(&(context->path));
	ft_close_heredoc(context);
}
