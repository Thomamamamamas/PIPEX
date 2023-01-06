/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:13:16 by tcasale           #+#    #+#             */
/*   Updated: 2023/01/06 15:34:27 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/pipex.h"

void	first_child_process_exec(t_pipex *t_px, int *fd, char **envp)
{
	int		id;
	char	*path;

	close(fd[0]);
	close(t_px->fd_outfile);
	if (dup2(t_px->fd_infile, 0) < 0 || dup2(fd[1], 1) < 0)
		exit(error_management(-12));
	path = get_correct_path(t_px, t_px->path, 0);
	if (path == NULL || check_cmd_file_valid(path) != 0)
	{
		error_management(check_cmd_file_valid(path));
		free(path);
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == 0)
		execve(path, t_px->cmd[0], envp);
	wait(NULL);
	close(fd[1]);
	close(t_px->fd_infile);
	free(path);
	exit(EXIT_SUCCESS);
}

int	parent_process_exec(t_pipex *t_px, int *fd, char **envp)
{
	int		id;
	int		res;
	char	*path;

	res = 0;
	if (t_px->no_infile == 1)
		return(-4);
	close(fd[1]);
	close(t_px->fd_infile);
	if (dup2(fd[0], 0) < 0 || dup2(t_px->fd_outfile, 1) < 0)
		return (-12);
	path = get_correct_path(t_px, t_px->path, t_px->nb_cmd - 1);
	if (path == NULL || check_cmd_file_valid(path) != 0)
	{
		res = check_cmd_file_valid(path);
		free(path);
		return (res);
	}
	id = fork();
	if (id == 0)
		execve(path, t_px->cmd[t_px->nb_cmd - 1], envp);
	wait(NULL);
	close(fd[0]);
	close(t_px->fd_outfile);
	free(path);
	return (0);
}

int	single_fork(t_pipex *t_px, char **envp)
{
	int	id;
	int	status;
	int	res;
	int	fd[2];

	res = 0;
	status = 0;
	if (pipe(fd) == -1)
		return (-11);
	id = fork();
	if (id != 0)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != EXIT_SUCCESS)
			{
				return (WEXITSTATUS(status));
			}
		}
		res = parent_process_exec(t_px, fd, envp);
	}
	else
		first_child_process_exec(t_px, fd, envp);
	return (res);
}
