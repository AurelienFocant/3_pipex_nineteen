/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_cmd_extraction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:56:31 by afocant           #+#    #+#             */
/*   Updated: 2024/07/17 16:36:18 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **envp)
{
	char	**env;
	char	**path;

	env = NULL;
	path = NULL;
	while (*envp)
	{
		env = ft_split(*envp, '=');
		if (!env)
			ft_perror_exit("Error parsing env", ENOENT, 4);
		if (ft_strncmp(env[0], "PATH", ft_strlen("PATH")) == 0)
		{
			path = (ft_split(env[1], ':'));
			ft_free_null_strv(env);
			/*
			if (!path)
				ft_perror_exit("No valid $PATH was provided", ENOENT, 5);
			// Should not exit !! Could be no envp but directly given an executable
			*/
			return (path);
		}
		ft_free_null_strv(env);
		envp++;
	}
	return (NULL);
}

char	*ft_prepend_path_cmd(char **path, char *cmd)
{
	char	*res;
	size_t	i;
	size_t	j;

	while (*path)
	{
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
		if (ft_check_if_cmd_is_executable(res))
			return (res);
		ft_free_null(res);
		path++;
	}
	ft_perror_exit("Can't find executable", ENOENT, 94);
	return (NULL);
}

void	ft_find_executable(t_context *context)
{
	int		curr_cmd_nb;

	//don t forget to check if /bin/ls was input
	curr_cmd_nb = context->curr_cmd_nb;
	// this split should be changed for awk and sed
	context->cmd = ft_split(context->argv[curr_cmd_nb + 2], ' ');
	if (context->cmd == NULL)
		ft_perror_exit("Can't find executable", ENOENT, 94);
	context->executable = ft_prepend_path_cmd(context->path, context->cmd[0]);
}
