#include "pipex.h"

int	first_child_process_exec(t_pipex *t_px, int *fd, char **envp)
{
	int	fd_infile;
	char	*env[] = {"wc", "-c"};

	fd_infile = open(t_px->infile, O_RDONLY);
	if (fd_infile < 0)
		return (-1);
	if (dup2(fd_infile, 0) < 0 || dup2(fd[1], 1) < 0)
		return (-1);
	close(fd[0]);
	close(fd_infile);
	close(fd[1]);
	return (0);
}

int	parent_process_exec(t_pipex *t_px, int *fd, char **envp)
{
	int	fd_outfile;
	int	n;
	int	status;
	char	**env;
	char	*path;
	
	waitpid(-1, &status, 0);
	fd_outfile = open(t_px->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_outfile < 0)
		return (-1);
	if (dup2(fd[0], 0) < 0 || dup2(fd_outfile , 1) < 0)
		return (-1);
	while (ft_strstr(envp[n], "PATH=") == 0)
		n++;
	env = ft_split(ft_substr(envp[n], 5, 500), ':');
	path = get_path(t_px, env);
	if (path == NULL)
		return (-1);
	execve(path, t_px->cmd[t_px->nb_cmd], envp);
	close(fd_outfile);
	close(fd[1]);
	return (0);
}

int	single_fork(t_pipex *t_px, char **envp)
{
	int	id;
	int	res;
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id != 0)
	{
		res = parent_process_exec(t_px, fd, envp);
	}
	else
	{
		res = first_child_process_exec(t_px, fd, envp);
	}
	if (res != 0)
		return (-1);
	return (0);
}

int	multiple_fork(t_pipex *t_px, char **envp)
{
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	t_px;
	int		res;

	if (argc >= 3)
	{
		t_px = parse_arg(argc, argv, envp);
		if (t_px.nb_cmd > 2)
			res = multiple_fork(&t_px, envp);
		else if (t_px.nb_cmd == 2)
			res = single_fork(&t_px, envp);
		else
			res = -1;
		free_t_pipex(&t_px);
	}
	else
		res = -1;
	printf("res = %d\n", res);
	if (res != 0)
		perror("Error\n");
	return (0);
}
