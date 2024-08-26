/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_context.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:58:39 by afocant           #+#    #+#             */
/*   Updated: 2024/07/25 17:02:10 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_check_heredoc(int argc, char **argv)
{
	if (argc < 6)
		return (0);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		return (1);
	else
		return (0);
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
