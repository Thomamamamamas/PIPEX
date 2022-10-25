#include "../headers/pipex.h"

int  heredoc(t_pipex *t_px, char **envp)
{
    ft_printf("%s\n", envp[0]);
    ft_printf("%d\n", t_px->nb_cmd);
    return (0);
}