/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcasale <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:27:07 by tcasale           #+#    #+#             */
/*   Updated: 2022/09/22 13:27:34 by tcasale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include "stdlib.h"
# include "stdio.h"
# include "unistd.h"
# include "fcntl.h"
# include "../srcs/libftprintf/ft_printf.h" 

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	int		fd_infile;
	int		fd_outfile;
	char	**path;
	char	***cmd;
	int		nb_cmd;
}			t_pipex;

//pipex
int				first_child_process_exec(t_pipex *t_px, int *fd, char **envp);
int				parent_process_exec(t_pipex *t_px, int *fd, char **envp);
int				single_fork(t_pipex *t_px, char **envp);
//pipex_multi_pipes
int				multiple_fork(t_pipex *t_px, char **envp);
//pipex_heredoc
int				heredoc(t_pipex *t_px, char **envp);
//parsing
t_pipex			parse_arg(int argc, char **argv, char **envp);
int				get_file_descriptor(char *file_name, int mode);
char			**get_path_variable(char **envp);
char			*get_correct_path(t_pipex *t_px, char **env, int nb_cmd);
//utils
void			free_t_pipex(t_pipex *t_px);
void			free_2d_str(char **str);
//errors_gestion
int				check_cmd_file_valid(char *file_name);
void			error_management(int code);
int				check_file_valid(t_pipex *t_px);
//pipex_debug
void			print_t_pipex(t_pipex t_px);

#endif
