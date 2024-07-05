#include <unistd.h>
#include <stdio.h>

#define CHILD 0

int main(int ac, char **av, char **env)
{
	size_t	n;
	size_t	nb_of_cmds;
	pid_t	pid;

	nb_of_cmds = 2;
	n = 0;
	while (n < nb_of_cmds)
	{
		pid = fork();
		if (pid == CHILD)
		{
			printf("I'm child nb %lu\n", n);
			return (1); // exec
		}
		else
		{
			printf("Parent with child %i\n", pid);
			//ft_wait_for_everyone
		}
		n++;
	}
}
