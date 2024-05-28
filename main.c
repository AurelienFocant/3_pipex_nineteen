#include "pipex.h"

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

#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		errno = 22;
		perror("You need 4 command line arguments !");
		exit(errno);
	}
	ft_get_path(envp);
}
