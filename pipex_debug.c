#include "pipex.h"

void	print_t_pipex(t_pipex t_px)
{
	int	n;
	int	m;

	n = 0;
	printf("infile = %s\n", t_px.infile);
	printf("outfile = %s\n", t_px.outfile);
	while (n < t_px.nb_cmd)
	{
		m = 0;
		while (t_px.cmd[n][m])
		{
			printf("commande %d argument %d = %s\n", n, m, t_px.cmd[n][m]);
			m++;
		}
		n++;
	}
	printf("total nombre de commande = %d\n", t_px.nb_cmd);
	n = 0;
	while (t_px.path[n])
	{
		printf("path %d = %s", n, t_px.path[n]);
		n++;
	}
}
