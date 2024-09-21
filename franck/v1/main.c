#include <unistd.h>

void	fill_ok(int (*okv)[2]);
int	set(int *views, int (*okviews)[2], int *map, int pos);

// Check prog param for errors & fill in 2D tab with expected view numbers
int	param(int argc, char **argv, int *views)
{
	char	*p;
	int		i;

	if (argc != 2)
		return (1);
	p = argv[1];
	while (*p != '\0')
		p++;
	if (p - argv[1] != 31)
		return (2);
	p = argv[1];
	i = 0;
	while (i < 16)
	{
		if (*p != '1' && *p != '2' && *p != '3' && *p != '4')
			return (3);
		views[i++] = *p - '0';
		p += 2;
	}
	return (0);
}

//stores all data
//checks param + create row checking index + launch map browsing
//read "readme.txt" for details
int	main(int argc, char **argv)
{
	int	views[16];
	int	retp;
	int	okviews[625][2];
	int	map[16];

	retp = param(argc, argv, views);
	if (retp == 0)
	{
		fill_ok(okviews);
		retp = 0;
		while (retp < 16)
			map[retp++] = 0;
		if (!set(views, okviews, map, 0))
			write(1, "Error\n", 6);
		return (4);
	}
	else
	{
		write(1, "Error\n", 6);
		return (retp);
	}
	return (0);
}

