/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:56:17 by afocant           #+#    #+#             */
/*   Updated: 2024/07/06 00:59:31 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute_child(t_context *context)
{
	char	*executable;
	char	**cmd;
	char	**envp;

	executable = context->executable;
	cmd = context->cmd;
	envp = context->envp;
	execve(executable, cmd, envp);
	ft_perror_exit("Execve has failed", errno, 753);
}

void	ft_pipex(t_context *context)
{
	int		curr_cmd_nb;
	pid_t	pid;

	curr_cmd_nb = 0;
	while (curr_cmd_nb < context->nb_of_cmds)
	{
		ft_prepare_pipe(context);
		pid = fork();
		if (pid == -1)
			ft_perror_exit("Fork failed", errno, 741);
		if (pid == CHILD)
		{
			context->curr_cmd_nb = curr_cmd_nb;
			ft_prepare_io(context);
			ft_find_executable(context);
			ft_set_up_redirection(context);
			ft_execute_child(context);
		}
		ft_close_pipes(context);
		curr_cmd_nb++;
	}
	ft_wait_for_all_children(context);
}

int		main(int argc, char **argv, char **envp)
{
	t_context	context;

	if (!ft_check_argc(argc))
		ft_perror_exit("Invalid number of arguments", EINVAL, 1);
	/*
	infile = argv[1];
	outfile = argv[argc - 1];
	if (!ft_check_valid_files(infile, outfile))
		ft_perror_exit("Invalid file", errno, 2);
	*/
	context = ft_initialise_context(argc, argv, envp);
	ft_pipex(&context);
	exit(0);
}
