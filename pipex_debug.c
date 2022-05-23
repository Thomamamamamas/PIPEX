#include "pipex.h"

void	print_t_pipex(t_pipex t_px)
{
	int	n;

	n = 0;
	printf("file1 = %s\n", t_px.file1);
	printf("file2 = %s\n", t_px.file2);
	while (n < t_px.cmd_len)
	{
		printf("commande %d = %s\n", n, t_px.cmd[n]);
		n++;
	}
	printf("nombre de commande = %d\n", t_px.cmd_len);
}
