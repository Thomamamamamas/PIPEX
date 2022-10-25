/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:16:55 by tcasale           #+#    #+#             */
/*   Updated: 2022/10/25 14:18:54 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

t_pipex	parse_arg(int argc, char **argv, char **envp)
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
	t_px.fd_infile = get_file_descriptor(t_px.infile, 0);
	t_px.fd_outfile = get_file_descriptor(t_px.outfile, 1);
	return (t_px);
}

int	get_file_descriptor(char *file_name, int mode)
{
	if (access(file_name, F_OK) == 0)
	{
		if (mode == 0)
			return (open(file_name, O_RDONLY));
		else
			return (open(file_name, O_RDWR | O_TRUNC));
	}
	else
		return (open(file_name, O_CREAT | O_RDWR, 0644));
}

char	**get_path_variable(char **envp)
{
	int		n;
	char	**tmp;

	n = 0;
	while (envp[n] && ft_strnstr(envp[n], "PATH=", ft_strlen(envp[n])) == 0)
		n++;
	if (envp[n] != NULL)
	{
		if (ft_strnstr(envp[n], "PATH=", ft_strlen(envp[n])) != 0)
			return (ft_split(ft_substr(envp[n], 5, 500), ':'));
	}
	tmp = (char **)malloc(sizeof(char *) * 1);
	tmp[0] = NULL;
	return (tmp);
}

char	*get_correct_path(t_pipex *t_px, char **env, int nb_cmd)
{
	int		n;
	char	*actual_path;

	if (t_px->cmd[nb_cmd][0])
	{
		if (access(t_px->cmd[nb_cmd][0], F_OK | X_OK) == 0)
			return (t_px->cmd[nb_cmd][0]);
	}
	n = 0;
	while (env[n] != NULL)
	{
		actual_path = ft_strjoin(ft_strjoin(env[n], "/"), t_px->cmd[nb_cmd][0]);
		if (access(actual_path, F_OK | X_OK) == 0)
			return (actual_path);
		free(actual_path);
		n++;
	}
	return (t_px->cmd[nb_cmd][0]);
}
