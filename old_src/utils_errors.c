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

int	check_cmd(char *cmd)
{
	if (access(cmd, X_OK) == -1)
		return (0);
	return (1);
}

int	check_infile(char *infile)
{
	if (access(infile, R_OK) == -1)
		return (0);
	return (1);
}

int	check_outfile(char *outfile)
{
	if (access(outfile, F_OK) == 0)
		if (access(outfile, W_OK) == -1)
			return (0);
	return (1);
}
