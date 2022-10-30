/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:26:30 by tcasale           #+#    #+#             */
/*   Updated: 2022/10/25 14:20:13 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	t_px;
	int		res;

	if (argc >= 5)
	{
		t_px = parse_arg(argc, argv, envp);
		check_mode(&t_px);
		res = check_file_valid(&t_px);
		if (t_px.path[0] == NULL && res == 0)
			res = -1;
		else if (t_px.is_heredoc == 1 && res == 0)
			res = heredoc_process(&t_px, envp);
		else if (t_px.nb_cmd > 2 && res == 0)
			res = multiple_fork(&t_px, envp);
		else if (t_px.nb_cmd == 2 && res == 0)
			res = single_fork(&t_px, envp);
		else if (res == 0)
			res = -2;
	}
	else
		res = -3;
	end_pipex(&t_px, res);
	return (res);
}