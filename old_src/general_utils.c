#include "pipex.h"

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
			free_null_strv(env);
			if (!path)
				perror_exit("No valid $PATH was provided", ENOENT);
			return (path);
		}
		free_null_strv(env);
		envp++;
	}
	return (NULL);
}

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

void	print_strv(char **strv)
{
	while (strv && *strv)
		printf("%s\n", *strv++);
}

void	free_null(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_null_strv(char **ptr)
{
	while (*ptr)
	{
		free_null(*ptr);
		ptr++;
	}
}
