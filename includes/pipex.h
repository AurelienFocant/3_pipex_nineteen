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

# define STDIN 0
# define STDOUT 1
# define STRERR 2

void	ft_fork_exec(char *envp[]);
void	ft_print_strv(char *strv[]);
char	**ft_get_path(char *envp[]);

int	check_args(int argc);
int	perror_exit(char *error, int errnb);

char	*prepend_path_cmd(char **path, char *cmd);
int	write_infile_to_pipe(int pipefd, char **argv, char **envp);
int	write_pipe_to_outfile(int pipefd, char **argv, char **envp);
int	pipe_exec(char **argv, char **envp);
int	fork_proc(char **argv, char **envp);
int	check_cmd(char *cmd);
int	check_infile(char *infile);
void	print_strv(char **strv);
void	free_null(void *ptr);
char	**get_path(char **envp);
int	main(int argc, char **argv, char **envp);

#endif
