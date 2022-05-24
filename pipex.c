#include "pipex.h"

int	first_child_process_exec(t_pipex *t_px, int *fd)
{
	int	fd_infile;

	close(fd[0]);
	fd_infile = open(t_px->infile, O_RDONLY);
	if (fd_infile < 0)
		return (1);
	if (dup2(fd_infile, 0) == -1 || dup2(fd[1], 1) == -1)
		return (2);
	close(fd[1]);
	close(fd_infile);
	return (0);
}

int	parent_process_exec(t_pipex *t_px, int *fd)
{
	int	fd_outfile;
	
	close(fd[1]);
	fd_outfile = open(t_px->outfile, O_RDONLY);
	if (fd_outfile < 0)
		return (1);
	if (dup2(fd[0], 0) == -1 || dup2(fd_outfile , 1) == -1)
		return (2);
	return (0);
}

int	single_fork(t_pipex *t_px)
{
	int	id;
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id != 0)
	{
		parent_process_exec(t_px, fd);
	}
	else
	{
		first_child_process_exec(t_px, fd);
	}
	return (0);
}

int	multiple_fork(t_pipex *t_px)
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
		if (t_px.nb_cmd > 2)
			res = multiple_fork(&t_px);
		else if (t_px.nb_cmd == 2)
			res = single_fork(&t_px);
		else
			res = 1;
	}
	if (res != 0)
		handle_error(res);
	free_t_pipex(&t_px);
	return (0);
}
