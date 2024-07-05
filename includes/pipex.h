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

# define READ	0
# define WRITE	1

typedef struct	s_context
{
	int		argc;
	char	**argv;
	char	**envp;
	int		nb_of_cmds;
	int		curr_cmd_nb;
	char	**path;
	char	**cmd;
	char	*executable;
	int		files_fd[2];
	int		pipes_fd[2];
}				t_context;

/*----------------  main.c  ---------------*/
void	ft_write_infile_to_pipe(char *cmd, char *infile, char *pipewrite);
void	ft_write_pipe_to_outfile(char *cmd, char *outfile, char *piperead);
void	ft_pipex(t_context *context);
int	main(int argc, char **argv, char **envp);

/*----------------  path_and_cmd_extraction.c  ---------------*/
char	**ft_get_path(char **envp);
char	*ft_prepend_path_cmd(char **path, char *cmd);
void	ft_extract_cmd(t_data *data, char *arg, char **envp);

/*----------------  prepare_context.c  ---------------*/
t_context	ft_initialise_context(int argc, char **argv, char **envp);
int			ft_open_file(char *file, int mode);
t_data		ft_prepare_io(t_context *context);
void		ft_prepare_pipe(t_context *context);

/*----------------  utils_check_files.c  ---------------*/
int	ft_check_if_cmd_is_executable(char *arg);
int	ft_check_argc(int argc);
int	ft_check_valid_files(char *infile, char *outfile);

/*----------------  utils_cleanup.c  ---------------*/
void	ft_wait_for_all_children(t_context *context);
void	ft_close_pipes(t_context context);

/*----------------  utils_manage_errors.c  ---------------*/
void	ft_free_null(char *ptr);
void	ft_free_null_strv(char **strv);
int		ft_perror_exit(char *error, int my_errno, int errnb);

#endif
