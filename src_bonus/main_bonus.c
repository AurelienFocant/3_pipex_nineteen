/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:35:28 by afocant           #+#    #+#             */
/*   Updated: 2024/09/23 12:35:40 by afocant          ###   ########.fr       */
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
