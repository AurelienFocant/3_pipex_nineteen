/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:56:17 by afocant           #+#    #+#             */
/*   Updated: 2024/08/27 01:01:56 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_context	context;

	if (!ft_check_argc(argc))
		ft_perror_exit("Invalid number of arguments", EINVAL, 1);
	context = ft_initialise_context(argc, argv, envp);
	ft_pipex(&context);
	exit(EXIT_SUCCESS);
}
