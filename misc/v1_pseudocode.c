	main

	check errors args

	find path env

	parse commands
		access - is executable ?
		if not
			append /
			append path
			access - is executable ?

	parse infile -- access ?

	pipe
		2 fd

	fork --
		child
			fork --
				child
					close pipe[read]
					read infile
						dup stdin to another fd
						dup2(infile, stdin)
					command 1
					--> write to pipe
				parent
					wait()
					close pipe[write]
					read pipe
						dup stdout to another fd
						dup2(outfile, stdout)
					command 2
					write to outfile
		parent
			wait
}

void	unknowns(void)
{
	unlink ??
}

void	errors(void)
{
	error on dup2 !!

	exec
	fork
	read
	pipe
	open
	if file exists or not
}

free cmd1 !!

free path -- check all mallocs


Don't forget to close all files !! in each process. Opened files AND pipes
plouf
