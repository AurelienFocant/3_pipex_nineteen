/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_context.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:58:39 by afocant           #+#    #+#             */
/*   Updated: 2024/07/06 00:58:49 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_context	ft_initialise_context(int argc, char **argv, char **envp)
{
	t_context	context;

	context.argc = argc;
	context.argv = argv;
	context.envp = envp;
	context.nb_of_cmds = argc - 3;
	context.curr_cmd_nb = -1;
	context.path = ft_get_path(envp);
	context.cmd = NULL;
	context.executable = NULL;
	context.files_fd[0] = -1;
	context.files_fd[1] = -1;
	context.pipes_fd[0] = -1;
	context.pipes_fd[1] = -1;
	return (context);
}

int			ft_open_file(char *file, int mode)
{
	int	fd;

	fd = -1;
	if (mode == READ)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			ft_perror_exit("Error opening infile", errno, 195);
	}
	else if (mode == WRITE)
	{
		fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0666);
		if (fd == -1)
			ft_perror_exit("Error opening outfile", errno, 196);
	}
	if (fd == -1)
		ft_perror_exit("Error opening file", errno, 197);
	return (fd);
}

void		ft_prepare_io(t_context *context)
{
	char	*infile;
	char	*outfile;
	int		last_cmd;

	infile = context->argv[1];
	outfile = context->argv[context->argc - 1];
	last_cmd = context->nb_of_cmds - 1;
	if (context->curr_cmd_nb == 0)
	{
		close(context->pipes_fd[STDIN_FILENO]);
		context->files_fd[STDIN_FILENO] = ft_open_file(infile, READ);
		context->files_fd[STDOUT_FILENO] = context->pipes_fd[STDOUT_FILENO];
	}
	else if (context->curr_cmd_nb == last_cmd)
	{
		context->files_fd[STDOUT_FILENO] = ft_open_file(outfile, WRITE);
		context->files_fd[STDIN_FILENO] = context->pipes_fd[STDIN_FILENO];
		close(context->pipes_fd[STDOUT_FILENO]);
	}
	else
	{
		context->files_fd[STDIN_FILENO] = context->pipes_fd[STDIN_FILENO];
		context->files_fd[STDOUT_FILENO] = context->pipes_fd[STDOUT_FILENO];
	}
}

void		ft_prepare_pipe(t_context *context)
{
	if (pipe(context->pipes_fd) == -1)
		ft_perror_exit("Pipe failed", errno, 454);
}

void		ft_set_up_redirection(t_context *context)
{
	if (dup2(context->files_fd[STDIN_FILENO], STDIN_FILENO) == -1)
		ft_perror_exit("Dup2 call on input has failed", errno, 524);
	if (dup2(context->files_fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
		ft_perror_exit("Dup2 call on output has failed", errno, 525);
}
