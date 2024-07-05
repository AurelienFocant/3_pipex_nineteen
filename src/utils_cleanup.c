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

void	ft_close_pipes(t_context context)
{
	close(context->pipes_fd[0]);
	close(context->pipes_fd[1]);
}
