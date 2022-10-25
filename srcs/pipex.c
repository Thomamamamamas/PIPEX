#include "../headers/pipex.h"

int	first_child_process_exec(t_pipex *t_px, int *fd, char **envp)
{
	char	*path;

	if (dup2(t_px->fd_infile, 0) < 0 || dup2(fd[1], 1) < 0)
		return (-1);
	path = get_correct_path(t_px, get_path_variable(envp), 0);
	if (path == NULL || check_cmd_file_valid(path) != 0)
	{
		error_management(check_cmd_file_valid(path));
		free(path);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	execve(path, t_px->cmd[0], envp);
	free(path);
	exit(EXIT_SUCCESS);
}

int	parent_process_exec(t_pipex *t_px, int *fd, char **envp)
{
	int		status;
	char	*path;

	waitpid(-1, &status, 0);
	if (dup2(fd[0], 0) < 0 || dup2(t_px->fd_outfile, 1) < 0)
		return (-1);
	path = get_correct_path(t_px, get_path_variable(envp), t_px->nb_cmd - 1);
	if (path == NULL || check_cmd_file_valid(path) != 0)
	{
		error_management(check_cmd_file_valid(path));
		free(path);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	execve(path, t_px->cmd[t_px->nb_cmd - 1], envp);
	free(path);
	exit(EXIT_SUCCESS);
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
		res = first_child_process_exec(t_px, fd, envp);
	return (res);
}
