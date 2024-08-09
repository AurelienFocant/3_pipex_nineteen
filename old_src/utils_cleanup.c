/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:59:13 by afocant           #+#    #+#             */
/*   Updated: 2024/07/25 16:18:09 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_wait_for_all_children(t_context *context)
{
	int	n;

	n = 0;
	while (n < context->nb_of_cmds)
	{
		wait(NULL);
		n++;
	}
}

void	ft_close_pipes(t_context *context)
{
	unsigned int	nb_of_pipes;
	unsigned int	n;

	nb_of_pipes = context->argc - 4 - context->heredoc;
	n = 0;
	while (n < (nb_of_pipes * 2))
	{
		close(context->pipes_fd[n]);
		n++;
	}
	free(context->pipes_fd);
}
