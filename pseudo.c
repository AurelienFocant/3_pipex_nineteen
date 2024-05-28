main

check errors args

find path env

parse commands -- access ?

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



unlink ??
