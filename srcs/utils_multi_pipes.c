/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_multi_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:15:36 by tcasale           #+#    #+#             */
/*   Updated: 2023/01/04 12:15:39 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/pipex.h"

void	close_unused(t_pipex *t_px, int i, int **fds)
{
	int	j;

	j = 0;
	while (j < t_px->nb_cmd)
	{
		if (i != j)
			close(fds[j][0]);
		if (i + 1 != j)
			close(fds[j][1]);
		j++;
	}
	if (i != 0)
		close(t_px->fd_infile);
	else if (i != t_px->nb_cmd - 1)
		close(t_px->fd_outfile);
}

void	end_close_pipes(t_pipex *t_px, int n, int **fds)
{
	if (n == 0)
		close(t_px->fd_infile);
	else if (n == t_px->nb_cmd - 1)
		close(t_px->fd_outfile);
	close(fds[n][0]);
	close(fds[n + 1][1]);
}

int	dup_correct_fd(t_pipex *t_px, int **fds, int n)
{
	if (n == 0)
	{
		if (dup2(t_px->fd_infile, 0) < 0 || dup2(fds[1][1], 1) < 0)
			return (-12);
	}
	else if (n == t_px->nb_cmd - 1)
	{
		if (dup2(fds[n][0], 0) < 0 || dup2(t_px->fd_outfile, 1) < 0)
			return (-12);
	}
	else
	{
		if (dup2(fds[n][0], 0) < 0 || dup2(fds[n + 1][1], 1) < 0)
			return (-12);
	}
	return (0);
}

int	**malloc_2d_array(int col, int line)
{
	int	n;
	int	**res;

	n = 0;
	res = (int **)malloc(sizeof(int *) * line);
	while (n < line)
		res[n++] = (int *)malloc(sizeof(int) * col);
	return (res);
}

int	wait_subprocesses(t_pipex *t_px, int n, int **fds)
{
	int	m;
	int	*status;

	status = (int *)malloc(sizeof(int) * t_px->nb_cmd);
	m = 0;
	while (m < t_px->nb_cmd - n)
	{
		wait(&status[n]);
		if (WIFEXITED(status[n]))
		{
			if (WEXITSTATUS(status[n]) != EXIT_SUCCESS)
			{
				free_2d_int(fds, t_px->nb_cmd);
				m = status[n];
				free(status);
				return (WEXITSTATUS(m));
			}
		}
		m++;
	}
	free(status);
	return (0);
}
