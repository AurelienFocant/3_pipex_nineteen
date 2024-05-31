#include "pipex.h"

int	fork_exec(char **argv)
{
	return (0);
}

int	check_cmd(char *cmd)
{
	if (access(cmd, X_OK) == -1)
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
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;

	path = NULL;
	if (!check_args(argc))
		perror_exit(NULL, EINVAL);
	infile = argv[1];
	cmd1 = argv[2];
	cmd2 = argv[3];
	outfile = argv[4];
	if (check_cmd(cmd1) && check_cmd(cmd2))
		return (fork_exec(argv));
	if (!check_cmd(argv[2]))
		path = get_path(envp);
	free(path);
}
