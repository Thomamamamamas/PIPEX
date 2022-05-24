#include "pipex.h"

int	handle_error(int res)
{
	return (0);
}

t_pipex	parse_arg(int argc, char **argv)
{
	t_pipex	t_px;
	char	**tmp;
	int		n;
	int		m;
	
	n = 0;
	t_px.infile = ft_strdup(argv[1]);
	t_px.outfile = ft_strdup(argv[argc - 1]);
	t_px.cmd = (char **)malloc(sizeof(char *) * argc - 3);
	t_px.arg = (char ***)malloc(sizeof(char **) * argc - 3);
	t_px.nb_arg = (int *)malloc(sizeof(int) * argc - 3);
	while (n < argc - 2)
	{
		m = 0;
		tmp = ft_split(argv[n + 2], ' ');
		t_px.cmd[n] = ft_strdup(tmp[0]);
		while (tmp[m])
			m++;
		t_px.nb_arg[n] = m - 1;
		t_px.arg[n] = (char **)malloc(sizeof(char *) * m);
		m = 0;
		while (m < t_px.nb_arg[n])
		{
			t_px.arg[n][m] = ft_strdup(tmp[m + 1]);
			m++;
		}
		n++;
	}
	t_px.nb_cmd = n - 1;
	print_t_pipex(t_px);
	return (t_px);
}

void	free_t_pipex(t_pipex *t_px)
{
	int	n;

	n = 0;
	free(t_px->infile);
	free(t_px->outfile);
	while (n < t_px->nb_cmd)
	{
		free(t_px->cmd[n]);
		n++;
	}
}
