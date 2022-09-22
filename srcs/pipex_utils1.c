/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:26:38 by tcasale           #+#    #+#             */
/*   Updated: 2022/09/22 13:11:10 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/pipex.h"

t_pipex	parse_arg(int argc, char **argv, char **envp)
{
	t_pipex	t_px;
	char	*tmp;
	int		n;

	n = 0;
	t_px.infile = ft_strdup(argv[1]);
	t_px.outfile = ft_strdup(argv[argc - 1]);
	t_px.cmd = (char ***)malloc(sizeof(char **) * argc - 3);
	while (ft_strnstr(envp[n], "PATH=", ft_strlen(envp[n])) == 0)
		n++;
	tmp = ft_substr(envp[n], 5, 1000);
	t_px.path = ft_split(tmp, ':');
	n = 0;
	while (n < argc - 2)
	{
		t_px.cmd[n] = ft_split(argv[n + 2], ' ');
		n++;
	}
	t_px.nb_cmd = n - 1;
	t_px.fd_infile = open(t_px.infile, O_RDONLY);
	t_px.fd_outfile = open(t_px.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
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

void	free_2d_str(char **str)
{
	int	n;

	n = 0;
	while (str[n] == NULL)
	{
		free(str[n]);
		n++;
	}
	free(str);
}

char	*get_path(t_pipex *t_px, char **env, int nb_cmd)
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
	return (NULL);
}
