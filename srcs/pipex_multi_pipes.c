#include "../headers/pipex.h"

int	multiple_fork(t_pipex *t_px, char **envp)
{
	int	n;
	int	id;
	int	fd[t_px->nb_cmd];

	n = 0;
    if (pipe(fd) == -1)
        return (1);
    while (n < t_px->nb_cmd)
    {
        id = fork();
        n++;
        if (id == 0)
            return (0);
    }
	ft_printf("%s\n", envp[0]);
	return (0);
}