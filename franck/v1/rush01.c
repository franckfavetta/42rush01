#include <stdio.h>
#include <unistd.h>

// Fills in index for further checking of one row
// row key = base 5 number of the row
void	fill_ok(int (*okv)[2])
{
	char	*cb;
	char	*rgt;
	char	*lft;
	int		i;

	lft = "4 3 3 3 2 2 3 2 3 3 2 2 2 2 2 2 2 2 1 1 1 1 1 1 ";
	rgt = "1 2 1 2 2 3 1 2 1 2 2 3 1 2 1 2 2 3 2 3 2 3 3 4 ";
	cb = "1234 1243 1324 1342 1423 1432 2134 2143 2314 2341 2413 2431 ";
	i = -1;
	while (++i < 12)
	{
		okv[(cb[i * 5] - '0') * 125 + (cb[i * 5 + 1] - '0') * 25 + (cb[i * 5 + 2
			] - '0') * 5 + cb[i * 5 + 3] - '0'][0] = lft[i * 2] - '0';
		okv[(cb[i * 5] - '0') * 125 + (cb[i * 5 + 1] - '0') * 25 + (cb[i * 5 + 2
			] - '0') * 5 + cb[i * 5 + 3] - '0'][1] = rgt[i * 2] - '0';
	}
	cb = "3124 3142 3214 3241 3412 3421 4123 4132 4213 4231 4312 4321 ";
	i = -1;
	while (++i < 12)
	{
		okv[(cb[i * 5] - '0') * 125 + (cb[i * 5 + 1] - '0') * 25 + (cb[i * 5 + 2
			] - '0') * 5 + cb[i * 5 + 3] - '0'][0] = lft[i * 2 + 24] - '0';
		okv[(cb[i * 5] - '0') * 125 + (cb[i * 5 + 1] - '0') * 25 + (cb[i * 5 + 2
			] - '0') * 5 + cb[i * 5 + 3] - '0'][1] = rgt[i * 2 + 24] - '0';
	}
}

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

// Checks if expected lft & rgh match this row thanks to index okv 
int	chk_row(int *row, int lft, int rgt, int (*okv)[2])
{
	int	key;

	if(row[0] == 0 || row[1] == 0 || row[2] == 0 || row[3] == 0)
		return (1);
	key = row[0] * 125 + row[1] * 25 + row[2] * 5 + row[3];
	if(okv[key][0] != lft || okv[key][1] != rgt)
		return (0);
	return (1);
}

int	chk_map(int *map, int *maptr, int *views, int (*okv)[2])
{
	return (chk_row(map + 0, views[8], views[12], okv) &&
		chk_row(map + 4, views[9], views[13], okv) &&
		chk_row(map + 8, views[10], views[14], okv) &&
		chk_row(map + 12, views[11], views[15], okv) &&
		chk_row(maptr + 0, views[0], views[4], okv) &&
		chk_row(maptr + 4, views[1], views[5], okv) &&
		chk_row(maptr + 8, views[2], views[6], okv) &&
		chk_row(maptr + 12, views[3], views[7], okv));
}

//Sets recursively a new value, then checks the map
//maptr = transposed map -> for easier checking (only row checking)
int	set(int *vw, int (*okv)[2], int *map, int pos)
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
			if (chk_map(map, maptr, vw, okv))
				if (set(vw, okv, map, pos + 1))
					return (1);
		}
		map[pos] = 0;
	}
	return (0);
}

// Skycraper Puzzle - Piscine42-2024/9
//   - Method: 
//      - A) Check incoming parameters
//           Return error codes:
//              Err1) No arguments or too many
//              Err2) Argument string too long or too short
//              Err3) Error in view numbers
//              Err4) No solution found
//      - B) Create a 2D tab index for expected view numbers 
//           (extracted from parameters)
//             row key -> value left 
//           & row key -> value right
//                Views tab order:
//                   0)col1up     1)col2up    2)col3up      3)col4up 
//                   4)col1down   5)col2down  6)col3down    7)col4down 
//                   8)row1left   9)row2left  10)row3left  11)row4left
//                  12)row1right 13)row2right 14)row3right 15)row4right
//      - C) Browse the map recursively placing one new value & incrementing it
//      - D) Check every time every row & every column
//             (checking factorized by transposing the map matrix)
//   - How to use:
//        > ./rush-01 "col1up col2up col3up col4up col1down col2down col3down 
//        col4down row1left row2left row3left row4left row1right row2right ro
//        w3right row4right"
//   - Example:
//        > ./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
//     Output:
//        1 2 3 4
//        2 3 4 1
//        3 4 1 2
//        4 1 2 3
int	main(int argc, char **argv)
{
	int	views[16];
	int	retp;
	int	okviews[1000][2];
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

