#include "pipex.h"

int	ft_check_if_cmd_is_executable(char *arg)
{
	if (access(arg, X_OK) == 0)
		return (TRUE);
	return (FALSE);
}

int	ft_check_argc(int argc)
{
	if (argc != 5)
		return (0);
	return (1);
}

int	ft_check_valid_files(char *infile, char *outfile)
{
	if (access(infile, R_OK) == -1)
		return (FALSE);
	if (access(outfile, F_OK) == 0)
		if (access(outfile, W_OK) == -1)
			return (FALSE);
	return (TRUE);
}
