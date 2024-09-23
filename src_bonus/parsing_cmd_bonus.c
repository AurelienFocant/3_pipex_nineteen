/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:36:22 by afocant           #+#    #+#             */
/*   Updated: 2024/09/23 12:36:31 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
