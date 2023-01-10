/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multi_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:14:03 by tcasale           #+#    #+#             */
/*   Updated: 2023/01/10 12:12:57 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/pipex.h"

int	multiple_fork(t_pipex *t_px, char **envp)
{
	int	n;
	int	res;
	int	*ids;
	int	**fds;

	res = 1;
	ids = (int *)malloc(sizeof(int) * t_px->nb_cmd);
	fds = pipes_2d_fd(t_px);
	n = 0;
	while (n < t_px->nb_cmd - 1)
	{
		ids[n] = fork();
		if (ids[n] == -1)
			return (1);
		if (ids[n] == 0)
			if (wait_subprocesses(t_px, n, fds) == 0)
				process_multi(t_px, n, fds, envp);
		n++;
	}
	free(ids);
	if (wait_subprocesses(t_px, n, fds) == 0)
		res = process_multi(t_px, n, fds, envp);
	free_2d_int(fds, t_px->nb_cmd + 1);
	return (res);
}

int	process_multi(t_pipex *t_px, int n, int **fds, char **envp)
{
	char	*path;
	int		id;

	close_unused(t_px, n, fds);
	if (dup_correct_fd(t_px, fds, n) == -1)
		exit(EXIT_FAILURE);
	path = get_correct_path(t_px, t_px->path, n);
	if (path == NULL || check_cmd_file_valid(path) != 0)
	{
		free(path);
		end_close_pipes(t_px, n, fds);
		if (n == t_px->nb_cmd - 1)
			return (-7);
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == 0)
		execve(path, t_px->cmd[n], envp);
	wait(NULL);
	free(path);
	end_close_pipes(t_px, n, fds);
	if (n == t_px->nb_cmd - 1)
		return (0);
	exit(EXIT_SUCCESS);
}
