#ifndef PROTOTYPES_PIPEX_H
# define PROTOTYPES_PIPEX_H

# include "pipex.h"

/*----------------  utils_cleanup.c  ---------------*/
void	ft_wait_for_all_children(t_context *context);
void	ft_close_pipes(t_context *context);

/*----------------  path_and_cmd_extraction.c  ---------------*/
char	**ft_get_path(char **envp);
char	*ft_cat_path_cmd(char **path, char *cmd);
char	*ft_prepend_path_cmd(char **path, char *cmd);
void	ft_parse_quotes(char *str);
char	**ft_parse_cmd(char *arg);
void	ft_find_executable(t_context *context);

/*----------------  utils_check_files.c  ---------------*/
int	ft_check_if_cmd_is_executable(char *arg);
int	ft_check_argc(int argc);
int	ft_check_valid_files(char *infile, char *outfile);

/*----------------  utils_manage_errors.c  ---------------*/
void	ft_free_null(char *ptr);
void	ft_free_null_strv(char **strv);
int		ft_perror_exit(char *error, int my_errno, int errnb);

/*----------------  main.c  ---------------*/
void	ft_execute_child(t_context *context);
void	ft_pipex(t_context *context);

/*----------------  prepare_context.c  ---------------*/
int		ft_check_heredoc(int argc, char **argv);
t_context	ft_initialise_context(int argc, char **argv, char **envp);

/*----------------  setup_redirection.c  ---------------*/
int			ft_open_file(char *file, int mode);
int	ft_create_heredoc(t_context *context);
void	ft_redirection_first_child(t_context *context);
void	ft_redirection_last_child(t_context *context);
void	ft_redirection_middle_children(t_context *context);
void		ft_setup_redirection(t_context *context);
void		ft_duplicate_fds(t_context *context);
void		ft_prepare_pipe(t_context *context);

#endif
