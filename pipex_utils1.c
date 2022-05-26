#include "pipex.h"

int	handle_error(int res)
{
	return (0);
}

t_pipex	parse_arg(int argc, char **argv, char **envp)
{
	t_pipex	t_px;
	char	*tmp;
	int		n;
	int		m;
	
	n = 0;
	t_px.infile = ft_strdup(argv[1]);
	t_px.outfile = ft_strdup(argv[argc - 1]);
	t_px.cmd = (char ***)malloc(sizeof(char **) * argc - 3);
	while (ft_strstr(envp[n], "PATH=") == 0)
		n++;
	tmp = ft_strstr(envp[n], "PATH=");
	t_px.path = ft_split(tmp, ':');
	n = 0;
	while (n < argc - 2)
	{
		m = 0;
		t_px.cmd[n] = ft_split(argv[n + 2], ' ');
		m = 0;
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
