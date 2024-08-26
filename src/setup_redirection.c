#include "pipex.h"

int			ft_open_file(char *file, int mode)
{
	int	fd;

	fd = -1;
	if (mode == READ)
		fd = open(file, O_RDONLY);
	else if (mode == WRITE)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (mode == APPEND)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		ft_perror_exit("Error opening file", errno, 197);
	return (fd);
}

int	ft_create_heredoc(t_context *context)
{
	int		fd;
	char	*line;

	fd = ft_open_file(".heredoc.tmp", WRITE);
	ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
	line = ft_get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(context->argv[2], line, ft_strlen(line) - 1) != 0)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		ft_putstr_fd(line, fd);
		line = ft_get_next_line(STDIN_FILENO);
	}
	close(fd);
	fd = ft_open_file(".heredoc.tmp", READ);
	return (fd);
}

void	ft_redirection_first_child(t_context *context)
{
	char	*infile;
	int		pipe_out;

	infile = context->argv[1];
	pipe_out = (context->curr_cmd_nb * 2 + 1);
	context->files_fd[STDOUT_FILENO] = context->pipes_fd[pipe_out];
	if (context->heredoc)
		context->files_fd[STDIN_FILENO] = ft_create_heredoc(context);
	else
		context->files_fd[STDIN_FILENO] = ft_open_file(infile, READ);
	ft_duplicate_fds(context);
	close(context->files_fd[STDIN_FILENO]);
}

void	ft_redirection_last_child(t_context *context)
{
	char	*outfile;
	int		pipe_in;

	outfile = context->argv[context->argc - 1];
	pipe_in = (context->curr_cmd_nb * 2 - 2);
	context->files_fd[STDIN_FILENO] = context->pipes_fd[pipe_in];
	if (context->heredoc)
		context->files_fd[STDOUT_FILENO] = ft_open_file(outfile, APPEND);
	else
		context->files_fd[STDOUT_FILENO] = ft_open_file(outfile, WRITE);
	ft_duplicate_fds(context);
	close(context->files_fd[STDOUT_FILENO]);
}

void	ft_redirection_middle_children(t_context *context)
{
	int		pipe_in;
	int		pipe_out;

	pipe_in = (context->curr_cmd_nb * 2 - 2);
	pipe_out = (context->curr_cmd_nb * 2 + 1);
	context->files_fd[STDIN_FILENO] = context->pipes_fd[pipe_in];
	context->files_fd[STDOUT_FILENO] = context->pipes_fd[pipe_out];
	ft_duplicate_fds(context);
}

void		ft_setup_redirection(t_context *context)
{
	int	first_cmd;
	int	last_cmd;

	first_cmd = 0;
	last_cmd = context->nb_of_cmds - 1;
	if (context->curr_cmd_nb == first_cmd)
		ft_redirection_first_child(context);
	else if (context->curr_cmd_nb == last_cmd)
		ft_redirection_last_child(context);
	else
		ft_redirection_middle_children(context);
}

void		ft_duplicate_fds(t_context *context)
{
	if (dup2(context->files_fd[STDIN_FILENO], STDIN_FILENO) == -1)
		ft_perror_exit("Dup2 call on input has failed", errno, 524);
	if (dup2(context->files_fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
		ft_perror_exit("Dup2 call on output has failed", errno, 525);
}

void		ft_prepare_pipe(t_context *context)
{
	int	n;

	context->pipes_fd = malloc(sizeof(int) * (context->nb_of_pipes * 2));
	if (context->pipes_fd == NULL)
		ft_perror_exit("Malloc on pipe array has failed", errno, 2);
	n = 0;
	while (n < context->nb_of_pipes * 2)
	{
		if (pipe(context->pipes_fd + n) == -1)
			ft_perror_exit("Pipe creation has failed", errno, 3);
		n += 2;
	}
}
