#include "pipex.h"

int	handle_error(int res)
{
	return (0);
}

t_pipex	parse_arg(int argc, char **argv)
{
	t_pipex	t_px;
	int		n;
	
	n = 2;
	t_px.file1 = ft_strdup(argv[1]);
	t_px.file2 = ft_strdup(argv[argc - 1]);
	t_px.cmd = (char **)malloc(sizeof(char *) * argc - 3);
	while (n < argc - 1)
	{
		t_px.cmd[n - 2] = ft_strdup(argv[n]);
		n++;
	}
	t_px.cmd_len = n - 2;
	return (t_px);
}

void	free_t_pipex(t_pipex *t_px)
{
	int	n;

	n = 0;
	free(t_px->file1);
	free(t_px->file2);
	while (n < t_px->cmd_len)
	{
		free(t_px->cmd[n]);
		n++;
	}
}

char	*ft_strdup(char *s)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	res = (char *)malloc(sizeof(*s) * len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

size_t	ft_strlen(char *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}
