#include "../headers/pipex.h"

int	**pipes_2d_fd(t_pipex *t_px)
{
	int	n;
	int	**fds;

	fds = malloc_2d_array(2, t_px->nb_cmd + 1);
	n = 0;
	while (n < t_px->nb_cmd + 1)
		if (pipe(fds[n++]) == -1)
			error_management(-11);
	return (fds);
}

int	**heredoc_pipes_2d_fd()
{
	int	n;
	int	**fds;

	fds = malloc_2d_array(2, 3 + 1);
	n = 0;
	while (n < 2 + 1)
		if (pipe(fds[n++]) == -1)
			error_management(-11);
	return (fds);	
}

void	heredoc_close_unused(t_pipex *t_px, int i, int **fds)
{
	int	j;

	j = 0;
	while (j < 3 + 1)
	{
		if (i != j)
			close(fds[j][0]);
		if (i + 1 != j)
			close(fds[j][1]);
		j++;
	}
	if (i != 2)
		close(t_px->fd_outfile);
}

void	heredoc_end_close_pipes(t_pipex *t_px, int n, int **fds)
{
	if (n == 2)
		close(t_px->fd_outfile);
	close(fds[n][0]);
	close(fds[n + 1][1]);
}