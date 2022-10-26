/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:34:47 by tcasale           #+#    #+#             */
/*   Updated: 2022/10/25 14:35:33 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	check_cmd_file_valid(char *file_name)
{
	if (access(file_name, F_OK) != 0)
		return (-4);
	if (access(file_name, X_OK) != 0)
		return (-5);
	return (0);
}

int	check_file_valid(t_pipex *t_px)
{
	if ((t_px->fd_infile < 0  && ft_strcmp(t_px->infile, "heredoc") != 0))
		return (-5);
	else if (t_px->fd_outfile < 0)
		return (-5);
	return (0);
}

void	error_management(int code)
{
	if (code == -1)
		perror("Error: Command not found");
	else if (code == -2)
		perror("");
	else if (code == -3)
		perror("Error: To few arguments");
	else if (code == -4)
		perror("Error: File doesn't exist");
	else if (code == -5)
		perror("Error: Permission denied");
}
