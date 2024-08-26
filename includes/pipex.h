#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

# include "pipex.h"
# include "libft.h"

# define FALSE	0
# define TRUE	1

# define CHILD	0

# define READ		0
# define WRITE		1
# define APPEND		2

typedef struct	s_context
{
	int				argc;
	char			**argv;
	char			**envp;
	char			**path;
	unsigned int	heredoc;
	int				nb_of_pipes;
	int				nb_of_cmds;
	int				curr_cmd_nb;
	char			**cmd;
	char			*executable;
	int				files_fd[2];
	int				*pipes_fd;
}				t_context;

# include "prototypes_pipex.h"

#endif
