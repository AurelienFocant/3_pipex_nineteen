#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

#include "pipex.h"
#include "libft.h"

# define STDIN 0
# define STDOUT 1
# define STRERR 2

void	ft_fork_exec(char *envp[]);
void	ft_print_strv(char *strv[]);
char	**ft_get_path(char *envp[]);

int	check_args(int argc);
int	perror_exit(char *error, int errnb);

#endif
