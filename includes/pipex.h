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

typedef struct	s_data
{
	int		files_fd[2];
	char	*exec;
	char	**cmd;
}				t_data;

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

/*----------------  check_files_utils.c  -----------------*/
int	ft_check_if_cmd_is_executable(char *arg);
int	ft_check_argc(int argc);
int	ft_check_valid_files(char *infile, char *outfile);

/*----------------  manage_errors_utils.c  ---------------*/
void	ft_free_null(char *ptr);
void	ft_free_null_strv(char **strv);
int		ft_perror_exit(char *error, int my_errno, int errnb);

/*----------------  populate_data_utils.c  ---------------*/
size_t	ft_count_commands(char **argv);
char	**ft_get_path(char **envp);
char	*ft_prepend_path_cmd(char **path, char *cmd);
void	ft_initialize_data(t_data *data);
void	ft_extract_cmd(t_data *data, char *arg, char **envp);

#endif
