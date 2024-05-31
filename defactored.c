#include "pipex.h"


void	ft_fork_exec(char *envp[])
{

	pid_t	pid;
	int	e;
	char	*argv[] = {"ls", "-l", NULL};
	char	*cmd = "/bin/ls";

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, argv, envp);
		perror("Could not find executable");
		exit(errno);
	}
	else
	{
		wait(NULL);
		printf("this is the parent process");
	}
}

void	ft_print_argv(char *argv[])
{
	while (argv && *argv)
		printf("%s\n", *argv++);
}

char	**ft_get_path(char *envp[])
{
	size_t	i;
	char	**envs;
	char	**path;

	envs = NULL;
	i = 0;
	while (envp[i])
	{
		envs = ft_split(envp[i], '=');
		if (ft_strncmp(envs[0], "jPATH", ft_strlen("PATH")) == 0)
			return (ft_split(envs[1], ':'));	
		i++;
	}
	if (!envp[i])
	{
		errno = ENOENT;
		perror("No valid $PATH env was provided");
		exit(errno);
	}
	return (NULL);
}

void	ft_print_errno(void)
{
	printf("errno is %i\n", errno);
}

int old_main(int argc, char *argv[], char *envp[])
{
	char	**path;
	char	*infile;

	path = NULL;
	if (argc != 5)
	{
		errno = 22;
		perror("You need 4 command line arguments !");
		exit(errno);
	}
	path = ft_get_path(envp);
	if (!path)
		printf("no path\n");

/*
	ft_print_argv(path);
	printf("\n\n\n");
	ft_print_argv(envp);
*/

	ft_print_errno();
	infile = argv[1];
	if (open(infile, O_RDONLY) == -1)
	{
		ft_print_errno();
		perror("error on open");
		exit(errno);
	}

	if (access(infile, R_OK) == -1)
	{
		perror("error on access");
		exit(errno);
	}
	else
		printf("%s\n", infile);

	ft_fork_exec(envp);
	exit(0);
}
