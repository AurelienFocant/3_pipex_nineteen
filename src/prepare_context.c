/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_context.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:58:39 by afocant           #+#    #+#             */
/*   Updated: 2024/09/09 14:26:49 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **envp)
{
	size_t	path_prefix;
	char	**path;

	path_prefix = ft_strlen("PATH=");
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", path_prefix) == EXIT_SUCCESS)
		{
			path = (ft_split((*envp + path_prefix), ':'));
			if (!path)
				ft_perror_exit("Error parsing path", ENOENT, 3);
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
	context.nb_of_cmds = argc - PROG_NAME - IO_FILES;
	context.nb_of_pipes = context.nb_of_cmds - 1;
	context.pipes_fd = NULL;
	context.executable = NULL;
	context.cmd = NULL;
	context.curr_cmd_nb = -1;
	context.files_fd[0] = -1;
	context.files_fd[1] = -1;
	return (context);
}
