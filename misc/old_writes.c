/*
void	ft_write_infile_to_pipe(char *cmd, char *infile, char *pipewrite)
{
	close(piperead) !!!!!
	if (dup2(infile, STDIN_FILENO) == -1 || dup2(pipewrite, STDOUT_FILENO) == -1)
		ft_perror_exit("Dup2 call failed", errno, 7);
	execve(cmd[0], cmd, envp);
	ft_free_null_strv(cmd);
	ft_perror_exit("Exec call failed", errno, 8);
}

void	ft_write_pipe_to_outfile(char *cmd, char *outfile, char *piperead)
{
	close(pipewrite) !!!!!
	if (dup2(piperead, STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
		ft_perror_exit("Dup2 call failed", errno, 9);
	execve(cmd[0], cmd, envp);
	ft_free_null_strv(cmd);
	ft_perror_exit("Exec call failed", errno, 8);
}
*/
