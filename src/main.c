#include "pipex.h"
void	ft_write_infile_to_pipe(char *cmd, char *infile, char *pipewrite)
{
	close(piperead) !!!!!
	if (dup2(infile, STDIN_FILENO) == -1 || dup2(pipewrite, STDOUT_FILENO) == -1)
		ft_perror_exit("Dup2 call failed", errno, 7);
	execve(cmd[0], cmd, envp);
	ft_free_null_strv(cmd);
	ft_perror_exit("Exec call failed", errno, 8);
}

void	ft_write_pipe_to_outfile(char *cmd, char *outfile, char *piperead)
{
	close(pipewrite) !!!!!
	if (dup2(piperead, STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
		ft_perror_exit("Dup2 call failed", errno, 9);
	execve(cmd[0], cmd, envp);
	ft_free_null_strv(cmd);
	ft_perror_exit("Exec call failed", errno, 8);
}

void	ft_find_executable(t_context context)
{
	char	**cmd;
	char	**executable;
	int		curr_cmd_nb;

	path = ft_get_path(context->envp);
	curr_cmd_nb = context->curr_cmd_nb;
	context.cmd = ft_split(argv[curr_cmd_nb + 2], ' ');
	cmd = ft_split(context->argv[curr_cmd_nb + 2], ' ');
	executable = ft_prepend_path_cmd(path, cmd[0]);
	
}

void	ft_pipex(t_context *context)
{
	int	curr_cmd_nb;

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
	ft_wait_for_all_children(nb_of_cmds);
}

int		main(int argc, char **argv, char **envp)
{
	char		*infile;
	char		*outfile;
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
