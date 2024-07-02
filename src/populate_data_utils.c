#include "pipex.h"

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

char	*ft_prepend_path_cmd(char **path, char *cmd)
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
		if (ft_check_if_cmd_is_executable(res))
			return (res);
		ft_free_null(res);
		path++;
	}
	ft_perror_exit("Can't find executable", ENOENT, 94);
	return (NULL);
}

void	ft_initialize_data(t_data *data)
{
	data->files_fd[0] = -1;
	data->files_fd[1] = -1;
	data->exec = NULL;
	data->cmd = NULL;
}

void	ft_extract_cmd(t_data *data, char *arg, char **envp)
{
	char	**path;

	data->cmd = ft_split(arg, ' ');
	if (!data->cmd)
		ft_perror_exit("Error splitting command", ENOENT, 17);
	if (ft_check_if_cmd_is_executable(data->cmd[0]))
	{
		data->exec = data->cmd[0];
		return ;
	}
	path = ft_get_path(envp);
	if (!path)
		ft_perror_exit("Couldn't find path", ENOENT, 18);
	ft_free_null_strv(path);	
}
