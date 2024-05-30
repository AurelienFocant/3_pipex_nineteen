#include "pipex.h"


void	ft_fork_exec(char *envp[])
{

	pid_t	pid;
	int	e;
	char	*argv[] = {"ls", "-l", NULL};
	char	*cmd;

	pid = fork();
	if (pid == 0)
	{
		e = execve("ls", argv, envp);
		//printf("return value of exec is %i\n", e);
		perror(NULL);
	}
	else
	{
		wait(NULL);
	}
}

void	ft_print_env(char *envp[])
{
	size_t	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

/*
void	ft_get_path(char *envp[])
{
	size_t	i;
	char	**envs;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		envs = ft_split(envp[i], '=');
		if (ft_strncmp(envs[0], "PATH", 256) == 0)
		{
			paths = ft_split(envs[1], ':');	
			break;
		}
		i++;
	}
	i = 0;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
}
*/

int main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		errno = 22;
		perror("You need 4 command line arguments !");
		exit(errno);
	}
	//ft_get_path(envp);
	//ft_print_env(envp);
	ft_fork_exec(envp);
}
