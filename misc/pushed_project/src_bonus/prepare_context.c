/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_context.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:58:39 by afocant           #+#    #+#             */
/*   Updated: 2024/08/29 15:50:14 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_check_heredoc(int argc, char **argv)
{
	if (argc < 6)
		return (0);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		return (1);
	else
		return (0);
}

char	**ft_get_path(char **envp)
{
	char	**env;
	char	**path;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", ft_strlen("PATH=")) == 0)
		{
			env = ft_split(*envp, '=');
			if (!env)
				ft_perror_exit("Error parsing env", ENOENT, 2);
			path = (ft_split(env[1], ':'));
			if (!path)
				ft_perror_exit("Error parsing path", ENOENT, 3);
			ft_free_null_strv(env);
			return (path);
		}
		envp++;
	}
	path = ft_split("", ' ');
	if (!path)
		ft_perror_exit("Error parsing path", ENOENT, 123);
	return (path);
}

t_context	ft_initialise_context(int argc, char **argv, char **envp)
{
	t_context	context;

	context.argc = argc;
	context.argv = argv;
	context.envp = envp;
	context.path = ft_get_path(envp);
	context.heredoc = ft_check_heredoc(argc, argv);
	context.nb_of_pipes = context.argc - 1 - 2 - 1 - context.heredoc;
	context.nb_of_cmds = argc - 3 - context.heredoc;
	context.curr_cmd_nb = -1;
	context.cmd = NULL;
	context.executable = NULL;
	context.files_fd[0] = -1;
	context.files_fd[1] = -1;
	context.pipes_fd = NULL;
	return (context);
}
