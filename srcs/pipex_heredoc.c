#include "../headers/pipex.h"

char  *get_heredoc(t_pipex *t_px)
{
	int		stop_heredoc;
	char	*line;
	char	*res;
	char	*tmp;

	stop_heredoc = 0;
	if (t_px->nb_cmd > 3)
		end_pipex(t_px, 6);
	res = (char *)malloc(sizeof(char) * 1);
	while (stop_heredoc == 0)
	{
		line = get_next_line(0);
		if (ft_strcmp(line, ft_strjoin(t_px->cmd[0][0], "\n")) == 0)
			stop_heredoc = 1;
		else
		{
			tmp = ft_strdup(res);
			free(res);
			res = (char *)malloc(sizeof(char) * ft_strlen(tmp) + ft_strlen(line) + 1);
			res = ft_strcat(res, tmp);
			res = ft_strcat(res, line);
			free(tmp);
		}
		free(line);
	}
	return (res);
}

int	heredoc_child_process_exec(t_pipex *t_px, int **fds, char **envp)
{
	int		id;
	char	*path;

	heredoc_close_unused(t_px, 0, fds);
	if (dup2(fds[0][0], 0) < 0 || dup2(fds[1][1], 1) < 0)
		exit(error_management(-12));
	path = get_correct_path(t_px, t_px->path, 1);
	if (path == NULL || check_cmd_file_valid(path) != 0)
	{
		error_management(check_cmd_file_valid(path));
		heredoc_end_close_pipes(t_px, 0, fds);
		free(path);
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == 0)
		execve(path, t_px->cmd[1], envp);
	wait(NULL);
	heredoc_end_close_pipes(t_px, 0, fds);
	free(path);
	exit(EXIT_SUCCESS);
}

int	heredoc_parent_process_exec(t_pipex *t_px, int **fds, char **envp)
{
	int		id;
	int		res;
	char	*path;

	res = 0;
	heredoc_close_unused(t_px, 1, fds);
	if (dup2(fds[1][0], 0) < 0 || dup2(t_px->fd_outfile, 1) < 0)
		return (-12);
	path = get_correct_path(t_px, t_px->path, 2);
	if (path == NULL || check_cmd_file_valid(path) != 0)
	{
		res = check_cmd_file_valid(path);
		free(path);
		return (res);
	}
	id = fork();
	if (id == 0)
		execve(path, t_px->cmd[2], envp);
	wait(NULL);
	heredoc_end_close_pipes(t_px, 1, fds);
	free(path);
	return (0);
}

int	heredoc_process(t_pipex *t_px, char **envp)
{
	char *heredoc_value;
	int	**fds;
	int	res;
	int	id;
	int	status;

	fds = heredoc_pipes_2d_fd();
	heredoc_value = get_heredoc(t_px);
	id = fork();
	if (id == 0)
	{
		write(fds[0][1], heredoc_value, ft_strlen(heredoc_value) + 1);
		free(heredoc_value);
		res = heredoc_child_process_exec(t_px, fds, envp);
	}
	else
	{
		free(heredoc_value);
		wait(&status);
		if (WIFEXITED(status) == 1)
		{
			if (WEXITSTATUS(status) != EXIT_SUCCESS)
				return (WEXITSTATUS(status));
		}
		res = heredoc_parent_process_exec(t_px, fds, envp);
	}
	return (res);
}