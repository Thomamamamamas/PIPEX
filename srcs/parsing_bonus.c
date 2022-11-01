#include "../headers/pipex.h"

t_pipex	parse_arg_bonus(int argc, char **argv, char **envp)
{
	t_pipex	t_px;
	int		n;

	n = 0;
	t_px.infile = ft_strdup(argv[1]);
	t_px.outfile = ft_strdup(argv[argc - 1]);
	t_px.cmd = (char ***)malloc(sizeof(char **) * argc - 3);
	t_px.path = get_path_variable(envp);
	while (n < argc - 2)
	{
		t_px.cmd[n] = ft_split(argv[n + 2], ' ');
		n++;
	}
	t_px.nb_cmd = n - 1;
	t_px.fd_infile = get_file_descriptor_bonus(t_px.infile, 0);
	t_px.fd_outfile = get_file_descriptor_bonus(t_px.outfile, 1);
	return (t_px);
}

int	get_file_descriptor_bonus(char *file_name, int mode)
{
	if (ft_strcmp(file_name, "here_doc") == 0)
		return (0);
	else if (access(file_name, F_OK) == 0)
	{
		if (mode == 0)
		{
			return (open(file_name, O_RDONLY));
		}
		else
			return (open(file_name, O_RDWR | O_TRUNC));
	}
	else
		return (open(file_name, O_CREAT | O_RDWR, 0644));
}

int	check_file_valid_bonus(t_pipex *t_px)
{
	if ((t_px->fd_infile < 0  && ft_strcmp(t_px->infile, "here_doc") != 0))
		return (-5);
	else if (t_px->fd_outfile < 0)
		return (-5);
	return (0);
}