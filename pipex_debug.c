#include "pipex.h"

void	print_t_pipex(t_pipex t_px)
{
	int	n;
	int	m;

	n = 0;
	printf("file1 = %s\n", t_px.infile);
	printf("file2 = %s\n", t_px.outfile);
	while (n < t_px.nb_cmd)
	{
		m = 0;
		printf("commande %d = %s\n", n, t_px.cmd[n]);
		while (m < t_px.nb_arg[n])
		{
			printf("	arguments %d = %s\n", m, t_px.arg[n][m]);
			m++;
		}
		printf("	total nombres d'arguments = %d\n", t_px.nb_arg[n]);
		n++;
	}
	printf("total nombre de commande = %d\n", t_px.nb_cmd);
}
