#include "pipex.h"
#include <stdio.h>

int	write_infile_to_pipe(int pipefd, char **argv, char **envp)
{
	char	*cmd1;
	char	**path;
	int		infile;

	path = NULL;
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		perror_exit("Couldn't open infile", errno);
	if (check_cmd(argv[2]))
		cmd1 = ft_strdup(argv[2]);
	else
	{
		path = get_path(envp);
		cmd1 = prepend_path_cmd(path, argv[2]);
		free_null(path);
	}
	if (!cmd1)
		return (-1);
	if (dup2(infile, STDIN_FILENO) == -1 || dup2(pipefd, STDOUT_FILENO) == -1)
		perror_exit("dup call failed", errno);
	if (execve(cmd1, ft_split(argv[2], ' '), envp))
		perror("Exec call failed");
	free_null(cmd1);
	return (EXIT_FAILURE);
}

int	write_pipe_to_outfile(int pipefd, char **argv, char **envp)
{
	char	*cmd2;
	char	**path;
	int		outfile;

	outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (outfile == -1)
		perror_exit("Couldn't open infile", errno);
	path = get_path(envp);
	cmd2 = prepend_path_cmd(path, argv[3]);
	free_null(path);
	if (!cmd2)
		return (-1);
	dup(STDIN_FILENO);
	dup2(pipefd, STDIN_FILENO);
	dup(STDOUT_FILENO);
	dup2(outfile, STDOUT_FILENO);
	if (execve(cmd2, ft_split(argv[3], ' '), envp) == -1)
		perror("Exec call failed");
	free_null(cmd2);
	return (EXIT_FAILURE);
}

int	pipe_exec(char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		perror_exit("Pipe failed", errno);
	pid = fork();
	if (pid == -1)
		perror_exit("Fork failed", errno);
	if (pid == 0)
	{
		close(pipefd[0]);
		write_infile_to_pipe(pipefd[1], argv, envp);
	}
	else
	{
		wait(NULL);
		close(pipefd[1]);
		write_pipe_to_outfile(pipefd[0], argv, envp);
	}
	return (EXIT_SUCCESS);
}

int	fork_proc(char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_exit("Fork failed", errno);
	if (pid == 0)
		pipe_exec(argv, envp);
	else
		wait(NULL);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	if (!check_args(argc))
		perror_exit(NULL, EINVAL);
	if (!check_infile(argv[1]))
		perror_exit("Infile doesn't exist", ENOENT);
	if (!check_outfile(argv[argc - 1]))
		perror_exit("Outfile doesn't have the right permissions", EACCES);
	if (check_cmd(argv[2]) && check_cmd(argv[3]))
		return (pipe_exec(argv, envp));
	fork_proc(argv, envp);
}
