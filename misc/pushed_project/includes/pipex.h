/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:13:18 by afocant           #+#    #+#             */
/*   Updated: 2024/08/28 13:52:51 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_context
{
	int				argc;
	char			**argv;
	char			**envp;
	char			**path;
	int				nb_of_pipes;
	int				nb_of_cmds;
	int				curr_cmd_nb;
	char			**cmd;
	char			*executable;
	int				files_fd[2];
	int				*pipes_fd;
}				t_context;

/*----------------  pipex.c  ---------------*/
void		ft_execute_child(t_context *context);
void		ft_pipex(t_context *context);
void		ft_prepare_pipe(t_context *context);

/*----------------  prepare_context.c  ---------------*/
t_context	ft_initialise_context(int argc, char **argv, char **envp);
char		**ft_get_path(char **envp);

/*----------------  path_and_cmd_extraction.c  ---------------*/
char		*ft_cat_path_cmd(char **path, char *cmd);
char		*ft_prepend_path_cmd(char **path, char *cmd);
void		ft_parse_quotes(char *str);
char		**ft_parse_cmd(char *arg);
void		ft_find_executable(t_context *context);

/*----------------  setup_redirection.c  ---------------*/
void		ft_redirection_first_child(t_context *context);
void		ft_redirection_last_child(t_context *context);
void		ft_setup_redirection(t_context *context);

/*----------------  utils_check_files.c  ---------------*/
int			ft_check_if_cmd_is_executable(char *arg);
int			ft_check_argc(int argc);
int			ft_check_valid_files(char *infile, char *outfile);

/*----------------  utils_cleanup.c  ---------------*/
void		ft_wait_for_all_children(t_context *context);
void		ft_close_pipes(t_context *context);
void		ft_free_null(char *ptr);
void		ft_free_null_strv(char **strv);
int			ft_perror_exit(char *error, int my_errno, int errnb);

/*----------------  utils_redirection.c  ---------------*/
int			ft_open_file(char *file, int mode);
void		ft_duplicate_fds(t_context *context);

#endif
