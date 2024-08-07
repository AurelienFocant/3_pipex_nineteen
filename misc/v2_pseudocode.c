__main
	-- check nb of argv

	-- initialise context to NULL
	-- setup context
		- total nb of commands
			if heredoc argc -4 ?
			else argc -3
		path = get_path
			if null, should not exit !!

	-- start pipex
		--setup pipes
			- count pipes total
			- malloc int * 2 (pipefd[2])
			- pipe function

		-- start fork
			---- CHILD process
				//has to be before executable finding because outfile is always created
				- setup redirection 
-- prepare io
					-- dup2 io
				- find executable
					-- if argv is X_OK, good
					-- extract **cmd ---> trim split
					-- prepend path until executable is found
				- close pipes
				- execute child


			---- PARENT process
				- close all pipes
				- wait for all children


feature-heredoc:
	chec argc >=5  now
	-- if argc >= 6 &&
	-- if argv[1] == strcmp here_doc

	nb_of_commands = argc - 4, not -3
	every curr_cmd_nb += 1

	first child open here_doc tmp file
	ft_putstr_fd to it using ft_gnl on stdin

	parent should unlink the tmp file ??
