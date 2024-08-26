/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:59:17 by afocant           #+#    #+#             */
/*   Updated: 2024/08/26 23:45:58 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		ft_perror_exit("Error opening file", errno, 197);
	return (fd);
}

int	ft_create_heredoc(t_context *context)
{
	int		fd;
	char	*line;

	fd = ft_open_file(".heredoc.tmp", WRITE);
	ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
	line = ft_get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(context->argv[2], line, ft_strlen(line) - 1) != 0)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		ft_putstr_fd(line, fd);
		line = ft_get_next_line(STDIN_FILENO);
	}
	close(fd);
	fd = ft_open_file(".heredoc.tmp", READ);
	return (fd);
}

void	ft_duplicate_fds(t_context *context)
{
	if (dup2(context->files_fd[STDIN_FILENO], STDIN_FILENO) == -1)
		ft_perror_exit("Dup2 call on input has failed", errno, 524);
	if (dup2(context->files_fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
		ft_perror_exit("Dup2 call on output has failed", errno, 525);
}
