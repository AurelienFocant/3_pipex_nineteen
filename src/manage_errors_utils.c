#include "pipex.h"

void	ft_free_null(char *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	ft_free_null_strv(char **strv)
{
	size_t	i;

	i = 0;
	while (strv[i])
		ft_free_null(strv[i++]);
	free(strv);
	strv = NULL;
}

int		ft_perror_exit(char *error, int my_errno, int errnb)
{
	if (!errno)
		errno = my_errno;
	perror(error);
	exit(errnb);
}
