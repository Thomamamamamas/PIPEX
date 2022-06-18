#include "pipex.h"

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
	tmp = ft_substr(envp[n], 5, 1000);
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
	free(tmp);
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

char	*get_path(t_pipex *t_px, char **env)
{
	int		n;
	char	*actual_path;

	n = 0;
	n = 0;
	while (env[n] != NULL)
	{
		actual_path = ft_strjoin(ft_strjoin(env[n], "/"), "wc");
		if (access(actual_path, F_OK | X_OK) == 0)
			return (actual_path);
		free(actual_path);
		n++;
	}
	return (NULL);
}
