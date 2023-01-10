/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:26:30 by tcasale           #+#    #+#             */
/*   Updated: 2023/01/10 12:59:27 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	t_px;
	int		res;

	if (argc == 5)
	{
		parse_arg(&t_px, argc, argv, envp);
		res = check_file_valid(&t_px);
		if (t_px.path[0] == NULL && res == 0)
			res = -1;
		else if (t_px.nb_cmd == 2 && res == 0)
			res = single_fork(&t_px, envp);
		else if (res == 0)
			res = -2;
	}
	else if (argc < 5)
		res = -3;
	else
		res = -15;
	end_pipex(&t_px, res);
	return (res);
}
