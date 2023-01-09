/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:26:38 by tcasale           #+#    #+#             */
/*   Updated: 2023/01/09 15:04:48 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/pipex.h"

void	free_t_pipex(t_pipex *t_px)
{
	int	n;
	int	m;

	n = 0;
	if (t_px->nb_cmd != 0)
	{
		while (n < t_px->nb_cmd)
		{
			m = 0;
			while (t_px->cmd[n][m] != NULL)
			{
				ft_putstr_fd(t_px->cmd[n][m], 2);
				ft_putstr_fd("\n", 2);
				free(t_px->cmd[n][m]);
				m++;
			}
			free(t_px->cmd[n]);
			n++;
		}
		free(t_px->cmd);
		free(t_px->infile);
		free(t_px->outfile);
		free_2d_str(t_px->path);
	}
}

void	free_2d_str(char **str)
{
	int	n;

	n = 0;
	while (str[n] != NULL)
	{
		free(str[n]);
		n++;
	}
	free(str);
}

void	free_2d_int(int **array, int len)
{
	int	n;

	n = 0;
	while (n < len)
	{
		free(array[n]);
		n++;
	}
	free(array);
}
