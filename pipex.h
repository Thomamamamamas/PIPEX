#ifndef PIPEX_H
#define PIPEX_H

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

typedef struct s_pipex
{
		char	*file1;
		char	*file2;
		char	**cmd;
		int		cmd_len;
}				t_pipex;

//pipex
int				child_process_exec(char *file, char *cmd);
int				parent_process_exec(char *file1, char *file2, char *cmd);
int				single_fork(int argc, char **argv);
int				multiple_fork(int argc, char **argv);
//pipex_utils
int				handle_error(int res);
t_pipex			parse_arg(int argc, char **argv);
void			free_t_pipex(t_pipex *t_px);
char			*ft_strdup(char *s);
size_t			ft_strlen(char *s);
//pipex_debug
void			print_t_pipex(t_pipex t_px);

#endif
