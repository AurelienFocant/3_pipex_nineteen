#include "pipex.h"
/*
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

void	ft_fork_processes(char *argv, char *envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefds[2];

	if (pipe(pipefds) == -1)
		ft_perror_exit("Pipe failed", errno, 4);
	pid1 = fork();
	if (pid1 == -1)
		ft_perror_exit("Fork failed", errno, 5);
	if (pid1 == 0)
		ft_write_infile_to_pipe();
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_perror_exit("Fork failed", errno, 6);
		if (pid2 == 0)
		{
			infile = open(argv[1], O_RDONLY);
			if (infile == -1)
				ft_perror_exit("Infile open failed", errno, 7);
			ft_write_pipe_to_outfile();
		}
		else
		{
			wait(NULL);
			wait(NULL);
			close(pipefds[STDIN_FILENO]);
			close(pipefds[STDOUT_FILENO]);
		}
	}
}
 */

void	ft_init_data_and_exec(size_t nb_of_cmds, char **argv, char **envp)
{
	size_t	i;
	t_data	data[nb_of_cmds];

	i = 0;
	while (i < nb_of_cmds)
		ft_initialize_data(&data[i++]);
	i = 0;
	while (i < nb_of_cmds)
	{
		ft_extract_cmd(&data[i], argv[i + 2], envp);
		i++;
	}
}

void	ft_wait_for_all_children(size_t nb_of_commands)
{
	size_t	i;

	i = 0;
	while (i < nb_of_commands)
	{
		wait(NULL);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*infile;
	char	*outfile;
	size_t	nb_of_commands;

	if (!ft_check_argc(argc))
		ft_perror_exit("Invalid number of arguments", EINVAL, 1);
	infile = argv[1];
	outfile = argv[argc - 1];
	if (!ft_check_valid_files(infile, outfile))
		ft_perror_exit("Invalid file", errno, 2);
	nb_of_commands = ft_count_commands(argv);
	ft_init_data_and_exec(nb_of_commands, argv, envp);
	ft_wait_for_all_children(nb_of_commands);
	exit(0);
}
