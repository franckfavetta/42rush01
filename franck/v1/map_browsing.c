#include <unistd.h>

int	chk_map(int *map, int *maptr, int *views, int (*okviews)[2]);

void	put_map(int *map)
{
	int	col;
	int	row;
	char c;

	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
		{
			c = map[row * 4 + col] + '0';
			write(1, &c, 1);
		}
		write(1, "\n", 1);
	}
}

//Sets recursively a new value, then checks the map
//maptr = transposed map -> for easier checking (only row checking)
int	set(int *views, int (*okviews)[2], int *map, int pos)
{
	int	i;
	int	maptr[16];

	if (pos == 16)
	{
		put_map(map);
		return (1);
	}
	else
	{
		i = -1;
		while (++i < 16)
			maptr[(i % 4) * 4 + (i / 4)] = map[i];
		i = 0;
		while (++i < 5)
		{
			map[pos] = i;
			if (chk_map(map, maptr, views, okviews))
				if (set(views, okviews, map, pos + 1))
					return (1);
		}
		map[pos] = 0;
	}
	return (0);
}

