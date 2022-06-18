#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		n;
	int		fd_infile;
	int		fd_outfile;
	int		fd_error;
	char	*tmp;
	char	*actual_path;
	char	**path;
	char	*env[] = {"wc", "-l", NULL};

	fd_infile = open("infile", O_RDONLY);
	fd_outfile = open("outfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
	fd_error = open("outfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_outfile < 0 || fd_infile < 0)
		return (1);
	if (dup2(fd_infile, 0) == -1 || dup2(fd_outfile , 1) == -1)
		return (2);
	dup2(fd_error, 2);
	n = 0;
	while (ft_strstr(envp[n], "PATH=") == 0)
		n++;
	tmp = ft_substr(envp[n], 5, 1000);
	path = ft_split(tmp, ':');
	n = 0;
	while (path[n] != NULL)
	{
		actual_path = ft_strjoin(ft_strjoin(path[n], "/"), "wc");
		//execve("/usr/bin/wc", env, envp);
		free(actual_path);
		n++;
	}
}
