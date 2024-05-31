#include "pipex.h"

int	perror_exit(char *error, int errnb)
{
	if (!errno)
		errno = errnb;
	perror(error);
	exit(errno);
}

int	check_args(int argc)
{
	if (argc != 5)
		return (0);
	return (1);
}
