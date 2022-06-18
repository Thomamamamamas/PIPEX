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
		char	**path;
		char	***cmd;
		int		nb_cmd;
}				t_pipex;

//pipex
int				first_child_process_exec(t_pipex *t_px, int *fd, char **envp);
int				parent_process_exec(t_pipex *t_px, int *fd, char **envp);
int				single_fork(t_pipex *t_px, char **envp);
int				multiple_fork(t_pipex *t_px, char **envp);
//pipex_utils1
t_pipex			parse_arg(int argc, char **argv, char **envp);
void			free_t_pipex(t_pipex *t_px);
char			*get_path(t_pipex *t_px, char **env);
//pipex_utils2
char			*ft_strdup(char *s);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlen(char *s);
char			*ft_strstr(char *haystack, char *needle);
char			*ft_substr(char *s, unsigned int start, size_t len);
//ft_split
char			**ft_split(char const *s, char c);
//pipex_debug
void			print_t_pipex(t_pipex t_px);

#endif
