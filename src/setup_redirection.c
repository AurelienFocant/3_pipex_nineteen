/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:43:45 by afocant           #+#    #+#             */
/*   Updated: 2024/09/23 18:35:42 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_redirection_first_child(t_context *context)
{
	char	*infile;
	int		pipe_out;

	infile = context->argv[1];
	pipe_out = (context->curr_cmd_nb * 2 + 1);
	context->files_fd[STDOUT_FILENO] = context->pipes_fd[pipe_out];
	context->files_fd[STDIN_FILENO] = ft_open_file(infile, READ);
	ft_duplicate_fds(context);
	close(context->files_fd[STDIN_FILENO]);
}

void	ft_redirection_last_child(t_context *context)
{
	char	*outfile;
	int		pipe_in;

	outfile = context->argv[context->argc - 1];
	pipe_in = (context->curr_cmd_nb * 2 - 2);
	context->files_fd[STDIN_FILENO] = context->pipes_fd[pipe_in];
	context->files_fd[STDOUT_FILENO] = ft_open_file(outfile, WRITE);
	ft_duplicate_fds(context);
	close(context->files_fd[STDOUT_FILENO]);
}

void	ft_setup_redirection(t_context *context)
{
	int	first_cmd;
	int	last_cmd;

	first_cmd = 0;
	last_cmd = context->nb_of_cmds - 1;
	if (context->curr_cmd_nb == first_cmd)
		ft_redirection_first_child(context);
	else if (context->curr_cmd_nb == last_cmd)
		ft_redirection_last_child(context);
}
