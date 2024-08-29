/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:25:55 by afocant           #+#    #+#             */
/*   Updated: 2024/08/27 01:00:55 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_execute_child(t_context *context)
{
	execve(context->executable, context->cmd, context->envp);
	ft_free_null(context->executable);
	ft_free_null_strv(context->path);
	ft_perror_exit("Execve has failed", errno, 12);
}

void	ft_pipex(t_context *context)
{
	int		curr_cmd_nb;
	pid_t	pid;

	ft_prepare_pipe(context);
	curr_cmd_nb = 0;
	while (curr_cmd_nb < context->nb_of_cmds)
	{
		pid = fork();
		if (pid == -1)
			ft_perror_exit("Fork failed", errno, 6);
		if (pid == CHILD)
		{
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
	ft_free_null_strv(context->path);
	if (context->heredoc)
		unlink(".heredoc.tmp");
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
