/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:44:26 by afocant           #+#    #+#             */
/*   Updated: 2024/09/24 20:43:57 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open_file(char *file, int mode)
{
	int	fd;

	fd = -1;
	if (mode == READ)
		fd = open(file, O_RDONLY);
	else if (mode == WRITE)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (mode == APPEND)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		ft_perror_exit("Error opening file", errno, 7);
	return (fd);
}

int	ft_prepare_heredoc(t_context *context)
{
	char	*delimiter;
	int		fd;
	char	*line;

	if (!context->heredoc)
		return (-1);
	delimiter = ft_strjoin(context->argv[2], "\n");
	if (!delimiter)
		ft_perror_exit("Malloc of here_doc delimiter has failed", ENOENT, 123);
	fd = ft_open_file(".heredoc.tmp", WRITE);
	ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
	line = ft_get_next_line(STDIN_FILENO);
	while (line && ft_strcmp(delimiter, line) != 0)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		ft_putstr_fd(line, fd);
		free(line);
		line = ft_get_next_line(STDIN_FILENO);
	}
	free(line);
	free(delimiter);
	close(fd);
	return (fd);
}

void	ft_close_heredoc(t_context *context)
{
	if (context->heredoc)
		unlink (".heredoc.tmp");
}

void	ft_duplicate_fds(t_context *context)
{
	if (dup2(context->files_fd[STDIN_FILENO], STDIN_FILENO) == -1)
		ft_perror_exit("Dup2 call on input has failed", errno, 8);
	if (dup2(context->files_fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
		ft_perror_exit("Dup2 call on output has failed", errno, 9);
}
