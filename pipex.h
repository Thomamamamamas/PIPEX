#ifndef PIPEX_H
#define PIPEX_H

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"

typedef struct s_pipex
{
		char	*infile;
		char	*outfile;
		char	**cmd;
		char	***arg;
		int		nb_cmd;
		int		*nb_arg;
}				t_pipex;

//pipex
int				first_child_process_exec(t_pipex *t_px, int *fd);
int				parent_process_exec(t_pipex *t_px, int *fd);
int				single_fork(t_pipex *t_px);
int				multiple_fork(t_pipex *t_px);
//pipex_utils1
int				handle_error(int res);
t_pipex			parse_arg(int argc, char **argv);
void			free_t_pipex(t_pipex *t_px);
//pipex_utils2
char			*ft_strdup(char *s);
size_t			ft_strlen(char *s);
//ft_split
char			**ft_split(char const *s, char c);
//pipex_debug
void			print_t_pipex(t_pipex t_px);

#endif
