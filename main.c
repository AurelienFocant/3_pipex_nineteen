#include "pipex.h"

char	*prepend_path_cmd(char **path, char *cmd)
{
	char	*res;
	size_t	i;
	size_t	j;

	while (*path)
	{
		res = malloc(sizeof(char) * (ft_strlen(*path) + ft_strlen(cmd) + 2));
		if (!res)
			return (NULL);
		i = 0;
		j = 0;
		while ((*path)[j])
			res[i++] = (*path)[j++];
		res[i++] = '/';
		j = 0;
		while (cmd[j] && cmd[j] != ' ')
			res[i++] = cmd[j++];
		res[i] = '\0';
		if (check_cmd(res))
			return (res);
		free_null(res);
		path++;
	}
	perror_exit("Can't find executable", ENOENT);
	return (NULL);
}

int	write_infile_to_pipe(int pipefd, char **argv, char **envp)
{
	char	*cmd1;
	char	**path;
	int		infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		perror_exit("Couldn't open infile", errno);
	path = get_path(envp);
	cmd1 = prepend_path_cmd(path, argv[2]);
	free_null(path);
	if (!cmd1)
		return (-1);
	dup(STDIN_FILENO);
	dup2(infile, STDIN_FILENO);
	dup(STDOUT_FILENO);
	dup2(pipefd, STDOUT_FILENO);
	execve(cmd1, ft_split(argv[2], ' '), envp);
	free_null(cmd1);
	return (EXIT_FAILURE);
}

int	write_pipe_to_outfile(int pipefd, char **argv, char **envp)
{
	char	*cmd2;
	char	**path;
	int		outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT);
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
	execve(cmd2, ft_split(argv[3], ' '), envp);
	free_null(cmd2);
	return (EXIT_FAILURE);

	return (0);
}

int	pipe_exec(char **argv, char **envp)
{
	pid_t	pid;
	int	pipefd[2];

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

int	check_cmd(char *cmd)
{
	if (access(cmd, X_OK) == -1)
		return (0);
	return (1);
}

int	check_infile(char *infile)
{
	if (access(infile, R_OK) == -1)
		return (0);
	return (1);
}

void	print_strv(char **strv)
{
	while (strv && *strv)
		printf("%s\n", *strv++);
}

void	free_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

char	**get_path(char **envp)
{
	char	**env;
	char	**path;

	env = NULL;
	path = NULL;
	while (*envp)
	{
		env = ft_split(*envp, '=');
		if (!env)
			perror_exit("Error parsing env", ENOENT);
		if (ft_strncmp(env[0], "PATH", ft_strlen("PATH")) == 0)
		{
			path = (ft_split(env[1], ':'));
			free_null(env);
			if (!path)
				perror_exit("No valid $PATH was provided", ENOENT);
			return (path);
		}
		free_null(env);
		envp++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	**path;

	path = NULL;
	if (!check_args(argc))
		perror_exit(NULL, EINVAL);
	if (!check_infile(argv[1]))
		perror_exit("Infile doesn't exist", ENOENT);
	if (check_cmd(argv[2]) && check_cmd(argv[3]))
		return (pipe_exec(argv, envp));
	fork_proc(argv, envp);
}
