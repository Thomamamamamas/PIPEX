#include "pipex.h"

int	child_process_exec(char *file, char *cmd)
{
	dup2()
}

int	parent_process_exec(char *file1, char *file2, char *cmd)
{
	return (0);
}

int	single_fork(int argc, char **argv)
{
	int	id;
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id != 0)
	{
		return (1);
	}
	else
	{
		return (2);
	}
	return (0);
}

int	multiple_fork(int argc, char **argv)
{
	return (0);
}

int	main(int argc, char **argv)
{
	t_pipex	t_px;
	int		res;
	

	if (argc >= 5)
	{
		t_px = parse_arg(argc, argv);
		if (argc > 5)
			res = multiple_fork(argc, argv);
		else if (argc == 5)
			res = single_fork(argc, argv);
		else
			res = 1;
	}
	if (res != 0)
		handle_error(res);
	free_t_pipex(&t_px);
	return (0);
}
