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

# define STDIN	0
# define STDOUT	1
# define STRERR	2

# define FALSE	0
# define TRUE	1

int	check_args(int argc);
int	perror_exit(char *error, int errnb);
int	check_cmd(char *cmd);
int	check_infile(char *infile);
int	check_outfile(char *outfile);

char	*prepend_path_cmd(char **path, char *cmd);
int	write_infile_to_pipe(int pipefd, char **argv, char **envp);
int	write_pipe_to_outfile(int pipefd, char **argv, char **envp);
int	pipe_exec(char **argv, char **envp);
int	fork_proc(char **argv, char **envp);
void	print_strv(char **strv);
void	free_null(char *ptr);
void	free_null_strv(char **ptr);
char	**get_path(char **envp);

#endif
