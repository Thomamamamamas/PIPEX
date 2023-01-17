/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:12:15 by tcasale           #+#    #+#             */
/*   Updated: 2023/01/10 13:21:33 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/pipex.h"

void	parse_arg_bonus(t_pipex *t_px, int argc, char **argv, char **envp)
{
	int		n;

	n = 0;
	t_px->infile = ft_strdup(argv[1]);
	t_px->outfile = ft_strdup(argv[argc - 1]);
	t_px->cmd = (char ***)malloc(sizeof(char **) * argc - 3);
	t_px->path = get_path_variable(envp);
	while (n < argc - 2)
	{
		t_px->cmd[n] = ft_split(argv[n + 2], ' ');
		n++;
	}
	t_px->nb_cmd = n - 1;
	t_px->fd_infile = get_file_descriptor_bonus(t_px, t_px->infile, 0);
	t_px->fd_outfile = get_file_descriptor_bonus(t_px, t_px->outfile, 1);
}

void	check_mode(t_pipex *t_px)
{
	if (ft_strcmp(t_px->infile, "here_doc") == 0)
		t_px->is_heredoc = 1;
	else
		t_px->is_heredoc = 0;
}

int	get_file_descriptor_bonus(t_pipex *t_px, char *file_name, int mode)
{
	if (access(file_name, F_OK) == 0)
	{
		if (mode == 0)
		{
			return (open(file_name, O_RDONLY));
		}
		else
			return (open(file_name, O_RDWR | O_TRUNC));
	}
	if (mode == 0)
	{
		t_px->no_infile = 1;
		return (open(file_name, O_CREAT | O_RDONLY, 0644));
	}
	else
		return (open(file_name, O_CREAT | O_RDWR, 0644));
}

int	check_file_valid_bonus(t_pipex *t_px)
{
	if ((t_px->fd_infile < 0))
		return (-5);
	else if (t_px->fd_outfile < 0)
		return (-5);
	return (0);
}
