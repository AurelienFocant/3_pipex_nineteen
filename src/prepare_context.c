/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_context.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:58:39 by afocant           #+#    #+#             */
/*   Updated: 2024/07/25 17:02:10 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	int		pipe_in;
	int		pipe_out;

	infile = context->argv[1];
	outfile = context->argv[context->argc - 1];
	last_cmd = context->nb_of_cmds - 1;
	pipe_in = (context->curr_cmd_nb * 2 - 2);
	pipe_out = (context->curr_cmd_nb * 2 + 1);

	if (context->curr_cmd_nb == 0)
	{
		if (context->heredoc)
		{
			// ft_setup_heredoc(context);
			return ;
		}
		else
		{
			context->files_fd[STDIN_FILENO] = ft_open_file(infile, READ);
			context->files_fd[STDOUT_FILENO] = context->pipes_fd[pipe_out];
		}
	}
	else if (context->curr_cmd_nb == last_cmd)
	{
		context->files_fd[STDOUT_FILENO] = ft_open_file(outfile, WRITE);
		context->files_fd[STDIN_FILENO] = context->pipes_fd[pipe_in];
	}
	else
	{
		context->files_fd[STDIN_FILENO] = context->pipes_fd[pipe_in];
		context->files_fd[STDOUT_FILENO] = context->pipes_fd[pipe_out];
	}
}

void		ft_set_up_redirection(t_context *context)
{
	if (dup2(context->files_fd[STDIN_FILENO], STDIN_FILENO) == -1)
		ft_perror_exit("Dup2 call on input has failed", errno, 524);
	if (dup2(context->files_fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
		ft_perror_exit("Dup2 call on output has failed", errno, 525);
}

void		ft_prepare_pipe(t_context *context)
{
	unsigned int	nb_of_pipes;
	unsigned int	n;

	nb_of_pipes = context->argc - 1 - 2 - 1;
	context->pipes_fd = malloc(sizeof(int) * (nb_of_pipes * 2));
	if (context->pipes_fd == NULL)
		ft_perror_exit("Pipe failed", errno, 453);
	n = 0;
	while (n < nb_of_pipes * 2)
	{
		if (pipe(context->pipes_fd + n) == -1)
			ft_perror_exit("Pipe failed", errno, 454);
		n += 2;
	}
}

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
	context.pipes_fd = NULL;
	context.heredoc = 0;
	return (context);
}
