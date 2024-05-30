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
		e = execve(cmd, argv, envp);
		printf("return value of exec is %i\n", e);
		perror(NULL);
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("this is the parent process");
	}
}

void	ft_print_env(char *envp[])
{
	size_t	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

char	**ft_get_path(char *envp[])
{
	size_t	i;
	char	**envs;

	envs = NULL;
	i = 0;
	while (envp[i])
	{
		envs = ft_split(envp[i], '=');
		if (ft_strncmp(envs[0], "PATH", ft_strlen("PATH")) == 0)
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

int main(int argc, char *argv[], char *envp[])
{
	char	**path;

	path = NULL;
	if (argc != 5)
	{
		errno = 22;
		perror("You need 4 command line arguments !");
		exit(errno);
	}
	path = ft_get_path(envp);
	while (path && *path)
		printf("%s\n", *path++);
	//ft_print_env(envp);
	//ft_fork_exec(envp);
}

/*
*/
