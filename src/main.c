#include "../includes/pipex.h"

void	ft_free_null(char *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	ft_free_null_strv(char **strv)
{
	while (*strv)
	{
		ft_free_null(*strv);
		strv++;
	}
}

int	ft_perror_exit(char *error, int errnb)
{
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
	size_t nb_of_files;
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
			ft_perror_exit("Error parsing env", ENOENT);
		if (ft_strncmp(env[0], "PATH", ft_strlen("PATH")) == 0)
		{
			path = (ft_split(env[1], ':'));
			ft_free_null_strv(env);
			if (!path)
				ft_perror_exit("No valid $PATH was provided", ENOENT);
			return (path);
		}
		ft_free_null_strv(env);
		envp++;
	}
	return (NULL);
}

int	ft_check_if_cmd_is_executable(char *cmd, char **envp)
{
	char	**path;

	if (access(cmd, X_OK) == 0)
		return (TRUE);
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

int main(int argc, char **argv, char **envp)
{
	char	*infile;
	char	*outfile;

	if (argc != 5)
		return (ft_perror_exit("invalid number of arguments", 1));
	infile = argv[1];
	outfile = argv[argc - 1];
	if (!ft_check_valid_files(infile, outfile))
		return (ft_perror_exit("invalid file", 2));
	if (!ft_check_all_cmds(argv, envp))
		return (ft_perror_exit("invalid command", 3));
	//ft_fork_exec();	
	exit(4);
}
