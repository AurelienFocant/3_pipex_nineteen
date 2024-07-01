#include "../includes/pipex.h"

void	ft_free_null(char *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	ft_free_null_strv(char **strv)
{
	size_t	i;

	i = 0;
	while (strv[i])
		ft_free_null(strv[i++]);
	free(strv);
	strv = NULL;
}

int	ft_perror_exit(char *error, int my_errno, int errnb)
{
	if (!errno)
		errno = my_errno;
	perror(error);
	exit(errnb);
}

int	ft_check_valid_files(char *infile, char *outfile)
{
	if (access(infile, R_OK) == -1)
		return (FALSE);
	if (access(outfile, F_OK) == 0)
		if (access(outfile, W_OK) == -1)
			return (FALSE);
	return (TRUE);
}

size_t	ft_count_commands(char **argv)
{
	size_t	nb_of_files;
	size_t	i;

	nb_of_files = 2;
	i = 0;
	while (argv[i])
		i++;
	return (i - nb_of_files);
}

char	**ft_get_path(char **envp)
{
	char	**env;
	char	**path;

	env = NULL;
	path = NULL;
	while (*envp)
	{
		env = ft_split(*envp, '=');
		if (!env)
			ft_perror_exit("Error parsing env", ENOENT, 4);
		if (ft_strncmp(env[0], "PATH", ft_strlen("PATH")) == 0)
		{
			path = (ft_split(env[1], ':'));
			ft_free_null_strv(env);
			if (!path)
				ft_perror_exit("No valid $PATH was provided", ENOENT, 5);
			return (path);
		}
		ft_free_null_strv(env);
		envp++;
	}
	return (NULL);
}

int	ft_check_if_cmd_is_executable(char *arg, char **envp)
{
	char	**path;

	if (access(arg, X_OK) == 0)
	{
		return (TRUE);
	}
	path = ft_get_path(envp);
	free(path);
	return (FALSE);
}

int	ft_check_all_cmds(char **argv, char **envp)
{
	size_t	i;
	size_t	nb_of_commands;

	nb_of_commands = ft_count_commands(argv);
	i = 0;
	while (i < nb_of_commands)
		ft_check_if_cmd_is_executable(argv[i++], envp);
	return (TRUE);
}

int	ft_check_argc(int argc)
{
	if (argc != 5)
		return (0);
	return (1);
}

void	ft_write_infile_to_pipe(char *cmd, char *infile, char *pipewrite)
{
	if (dup2(infile, STDIN_FILENO) == -1 || dup2(pipewrite, STDOUT_FILENO) == -1)
		ft_perror_exit("Dup2 call failed", errno, 7);
	execve(cmd[0], cmd, envp);
	ft_free_null_strv(cmd);
	ft_perror_exit("Exec call failed", errno, 8);
}

void	ft_write_pipe_to_outfile(char *cmd, char *outfile, char *piperead)
{
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

int	main(int argc, char **argv, char **envp)
{
	char	*infile;
	char	*outfile;

	if (!ft_check_argc(argc))
		ft_perror_exit("Invalid number of arguments", EINVAL, 1);
	infile = argv[1];
	outfile = argv[argc - 1];
	if (!ft_check_valid_files(infile, outfile))
		ft_perror_exit("Invalid file", errno, 2);
	if (!ft_check_all_cmds(argv, envp))
		ft_perror_exit("Invalid command", errno, 3);
	ft_fork_processes();
	exit(4);
}
