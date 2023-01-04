/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:56:09 by tcasale           #+#    #+#             */
/*   Updated: 2023/01/04 12:17:16 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/pipex.h"

void	print_t_pipex(t_pipex *t_px)
{
	int	n;
	int	m;

	n = 0;
	printf("infile = %s\n", t_px->infile);
	printf("outfile = %s\n", t_px->outfile);
	while (n < t_px->nb_cmd)
	{
		m = 0;
		while (t_px->cmd[n][m])
		{
			printf("commande %d argument %d = %s\n", n, m, t_px->cmd[n][m]);
			m++;
		}
		n++;
	}
	printf("total nombre de commande = %d\n", t_px->nb_cmd);
	n = 0;
	while (t_px->path[n])
	{
		printf("path %d = %s", n, t_px->path[n]);
		n++;
	}
}

void	print_fd_state_multi_pipe(t_pipex *t_px, int **fds)
{
	int	n;

	n = 0;
	while (n < t_px->nb_cmd)
	{
		ft_printf("_________________\n");
		ft_printf("file descriptor numéro : %d\n", n);
		ft_printf("entrée : %d", fds[n][0]);
		ft_printf("sortie : %d", fds[n][1]);
		ft_printf("_________________\n");
		n++;
	}
}
