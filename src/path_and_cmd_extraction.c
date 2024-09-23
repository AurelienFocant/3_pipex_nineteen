/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_cmd_extraction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:56:31 by afocant           #+#    #+#             */
/*   Updated: 2024/09/23 13:37:11 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_cat_path_cmd(char **path, char *cmd)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = malloc(sizeof(char) * (ft_strlen(*path) + ft_strlen(cmd) + 2));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while ((*path)[j])
		res[i++] = (*path)[j++];
	res[i++] = '/';
	j = 0;
	while (cmd[j] && cmd[j] != ' ')
		res[i++] = cmd[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_prepend_path_cmd(char **path, char *cmd)
{
	char	*res;
	int		permission_denied;

	permission_denied = FALSE;
	while (path && *path)
	{
		res = ft_cat_path_cmd(path, cmd);
		if (!res)
			return (NULL);
		if (ft_check_if_cmd_is_executable(res))
			return (res);
		else
		{
			if (errno == EACCES)
				permission_denied = TRUE;
			ft_free_null((void **) &res);
			path++;
		}
	}
	if (permission_denied)
		errno = EACCES;
	return (NULL);
}

char	*ft_find_full_path(char **path, char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (ft_check_if_cmd_is_executable(cmd))
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	else
		return (ft_prepend_path_cmd(path, cmd));
}

void	ft_find_executable(t_context *context)
{
	int		curr_cmd;

	curr_cmd = context->curr_cmd_nb + 2;
	context->cmd = ft_parse_cmd(context->argv[curr_cmd]);
	if (!context->cmd || !*(context->cmd))
		ft_cmd_perror("Can't find executable", ENOENT, 10);
	context->executable = ft_find_full_path(context->path, context->cmd[0]);
	if (!context->executable)
		ft_cmd_perror(context->cmd[0], ENOENT, 11);
}
