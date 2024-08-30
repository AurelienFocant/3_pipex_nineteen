/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_cmd_extraction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:56:31 by afocant           #+#    #+#             */
/*   Updated: 2024/08/29 17:44:52 by afocant          ###   ########.fr       */
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

	if (ft_check_if_cmd_is_executable(cmd))
		return (ft_strdup(cmd));
	while (path && *path)
	{
		res = ft_cat_path_cmd(path, cmd);
		if (!res)
			return (NULL);
		if (ft_check_if_cmd_is_executable(res))
			return (res);
		ft_free_null(res);
		path++;
	}
	return (NULL);
}

void	ft_parse_quotes(char *str)
{
	unsigned int	i;
	unsigned char	bell;

	bell = 007;
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			str[i] = bell;
		if (ft_isquote(str[i]))
		{
			if (str[i - 1] != '\\')
				str[i] = bell;
			while (str[i] && !ft_isquote(str[i]))
				i++;
			if (ft_isquote(str[i]))
				if (str[i - 1] != '\\')
					str[i] = bell;
		}
		i++;
	}
}

char	**ft_parse_cmd(char *arg)
{
	char			**split_cmd;

	ft_parse_quotes(arg);
	split_cmd = ft_split(arg, 007);
	if (!split_cmd)
		return (NULL);
	return (split_cmd);
}

void	ft_find_executable(t_context *context)
{
	int		curr_cmd;

	curr_cmd = context->curr_cmd_nb + 2;
	context->cmd = ft_parse_cmd(context->argv[curr_cmd]);
	if (!context->cmd || !*(context->cmd))
		ft_perror_exit("Can't find executable", ENOENT, 10);
	context->executable = ft_prepend_path_cmd(context->path, context->cmd[0]);
	if (!context->executable)
		ft_perror_exit("Can't find executable", ENOENT, 11);
}
