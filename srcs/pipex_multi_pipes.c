#include "../headers/pipex.h"

int	multiple_fork(t_pipex *t_px, char **envp)
{
	int	n;
	int	id;
	int	*ids;
	int	**fds;

	n = 0;
	ids = (int *)malloc(sizeof(int) * t_px->nb_cmd + 1);
	fds = malloc_2d_array(2, t_px->nb_cmd);
	while (n < t_px->nb_cmd)
		if (pipe(fds[n++]) == -1)
			return (1);
	n = 0;
	while (n < t_px->nb_cmd)
	{
		id = fork();
		if (id == -1)
			return (1);
		if (id == 0)
			return (0);
		ids[n] = id;
		if (id == ids[0])
		{
			if (dup2(t_px->fd_infile, 0) < 0 || dup2(fds[n + 1][1], 1) < 0)
				return (-1);
		}
		else if (id == ids[t_px->nb_cmd])
		{
			if (dup2(fds[t_px->nb_cmd][0], 0) < 0 || dup2(t_px->fd_outfile, 1) < 0)
				return (-1);
		}
		else
		{
			if (dup2(fds[n][0], 0) < 0 || dup2(fds[n + 1][1], 1) < 0)
				return (-1);
		}
		process_exec_multi(t_px, n, envp);
		n++;
	}
	return (0);
}

int	process_exec_multi(t_pipex *t_px, int n, char **envp)
{
	char	*path;

	path = get_correct_path(t_px, get_path_variable(envp), n);
	if (path == NULL || check_cmd_file_valid(path) != 0)
	{
		error_management(check_cmd_file_valid(path));
		free(path);
		return (1);
	}
	execve(path, t_px->cmd[n], envp);
	free(path);
	return (0);
}