#include "../headers/pipex.h"

void	close_unused(t_pipex *t_px, int i, int *ids, int **fds)
{
	int	j;

	j = 0;
	if (ids[i] == 0)
	{
		while (j < t_px->nb_cmd)
		{
			if (i != j)
				close(fds[j][0]);
			if (i + 1 != j)
				close(fds[j][1]);
			j++;
		}
	}
}

int	**malloc_2d_array(int col, int line)
{
	int	n;
	int	**res;

	n = 0;
	res = (int **)malloc(sizeof(int *) * line);
	while (n < line)
		res[n++] = (int *)malloc(sizeof(int) * col);
	return (res);
}