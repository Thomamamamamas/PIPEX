/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:34:47 by tcasale           #+#    #+#             */
/*   Updated: 2023/01/04 13:08:45 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	end_pipex(t_pipex *t_px, int code)
{
	if (code != 0)
		error_management(code);
	free_t_pipex(t_px);
}

int	check_cmd_file_valid(char *file_name)
{
	if (access(file_name, F_OK) != 0)
		return (-7);
	if (access(file_name, X_OK) != 0)
		return (-5);
	return (0);
}

int	check_file_valid(t_pipex *t_px)
{
	if (t_px->fd_infile < 0)
		return (-5);
	else if (t_px->fd_outfile < 0)
		return (-5);
	return (0);
}

int	error_management(int code)
{
	if (code == -1)
		ft_putstr_fd("Error: Command not found\n", 2);
	else if (code == -2)
		ft_putstr_fd("", 2);
	else if (code == -4)
		ft_putstr_fd("Error: File doesn't exist\n", 2);
	else if (code == -5)
		ft_putstr_fd("Error: Permission denied\n", 2);
	else if (code == -7)
		ft_putstr_fd("Error: Command not found\n", 2);
	else if (code == -8)
		ft_putstr_fd("Error: No such file or directory", 2);
	else if (code == -11)
		ft_putstr_fd("Error: Pipes doesn't open\n", 2);
	else if (code == -12)
		ft_putstr_fd("Error: Dup2 doesn't work\n", 2);
	else if (code == -15)
		ft_putstr_fd("Error: To much arguments\n", 2);
	return (code);
}
