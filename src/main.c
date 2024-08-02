/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:56:17 by afocant           #+#    #+#             */
/*   Updated: 2024/07/25 17:10:32 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute_child(t_context *context)
{
	execve(context->executable, context->cmd, context->envp);
	// should free all the bloody malloc !
	ft_perror_exit("Execve has failed", errno, 753);
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
			ft_perror_exit("Fork failed", errno, 741);
		if (pid == CHILD)
		{
			context->curr_cmd_nb = curr_cmd_nb;
			ft_find_executable(context);
			ft_prepare_io(context);
			ft_set_up_redirection(context);
			ft_close_pipes(context);
			ft_execute_child(context);
		}
		curr_cmd_nb++;
	}
	ft_close_pipes(context);
	ft_wait_for_all_children(context);
}

int		main(int argc, char **argv, char **envp)
{
	t_context	context;

	if (!ft_check_argc(argc))
		ft_perror_exit("Invalid number of arguments", EINVAL, 1);
	context = ft_initialise_context(argc, argv, envp);
	ft_pipex(&context);
	exit(0);
}
