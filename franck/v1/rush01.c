#include <stdio.h>
#include <unistd.h>

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
		okv[(cb[i * 5] - '0') * 64 + (cb[i * 5 + 1] - '0') * 16 + (cb[i * 5 + 2
			] - '0') * 4 + cb[i * 5 + 3] - '0'][0] = lft[i * 2] - '0';
		okv[(cb[i * 5] - '0') * 64 + (cb[i * 5 + 1] - '0') * 16 + (cb[i * 5 + 2
			] - '0') * 4 + cb[i * 5 + 3] - '0'][1] = rgt[i * 2] - '0';
	}
	cb = "3124 3142 3214 3241 3412 3421 4123 4132 4213 4231 4312 4321 ";
	i = -1;
	while (++i < 12)
	{
		okv[(cb[i * 5] - '0') * 64 + (cb[i * 5 + 1] - '0') * 16 + (cb[i * 5 + 2
			] - '0') * 4 + cb[i * 5 + 3] - '0'][0] = lft[i * 2 + 24] - '0';
		okv[(cb[i * 5] - '0') * 64 + (cb[i * 5 + 1] - '0') * 16 + (cb[i * 5 + 2
			] - '0') * 4 + cb[i * 5 + 3] - '0'][1] = rgt[i * 2 + 24] - '0';
	}
}

//Return error codes:
// 1) No arguments or too many
// 2) Argument string too long or too short
// 3) View numbers error
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

void	all_comb(int *views, int (*okv)[2])
{
	unsigned int	c;

	c = 0;
	while (c <= 4294967295)
	{
		c++;
	}
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

int	chk(int *row, int lft, int rgt, int (*okv)[2])
{
	int	idcomb;

	if(row[0] == 0 || row[1] == 0 || row[2] == 0 || row[3] == 0)
		return (1);
	idcomb = row[0] * 64 + row[1] * 16 + row[2] * 4 + row[3];
	if(okv[idcomb][0] != lft || okv[idcomb][1] != rgt)
		return (0);
	return (1);
}

//maptr = transposed map -> for easier checking
int	set(int *vw, int (*okv)[2], int *map, int pos)
{
	int	i;
	int	maptr[16];

	if (pos == 16)
	{
		write(1, "found\n", 6);
		put_map(map);
		write(1, "found\n", 6);
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
			if (chk(map + 0, vw[8], vw[12], okv) && chk(map + 4, vw[9], vw[13], okv) &&
				chk(map + 8, vw[10], vw[14], okv) && chk(map + 12, vw[11], vw[15], okv) &&
				chk(maptr + 0, vw[0], vw[4], okv) && chk(maptr + 4, vw[1], vw[5], okv) &&
				chk(maptr + 8, vw[2], vw[6], okv) && chk(maptr + 12, vw[3], vw[7], okv))
				set(vw, okv, map, pos + 1);
		}
		/*
		*/
	}
	return (0);
}

//views tab order:
//  0)col1up     1)col2up    2)col3up      3)col4up 
//  4)col1down   5)col2down  6)col3down    7)col4down 
//  8)row1left   9)row2left  10)row3left  11)row4left
// 12)row1right 13)row2right 14)row3right 15)row4right
int	main(int argc, char **argv)
{
	int	views[16];
	int	retp;
	int	okviews[314][2];
	int	map[16];
	retp = param(argc, argv, views);
	if (retp == 0)
	{
		fill_ok(okviews);
		retp = 0;
		while (retp < 16)
			map[retp++] = 0;
		set(views, okviews, map, 0); 
	}
	else
	{
		write(1, "Error\n", 6);
		return (retp);
	}
	return (0);
}

/*
		int i;
		//for (i=0; i<16; i++)
		//	printf("%d  ", views[i]); 
		//write(1, "ici", 3);
		for (i=0; i<314; i++)
			okviews[i][0] = 0; 
		for (i=0; i<314; i++)
			okviews[i][1] = 0; 

		for (i=0; i<314; i++)
			if (okviews[i][0] != 0)
				printf("%d %d %d\n", okviews[i][0], i, okviews[i][1]); 


		map[3] = 7;
		map[6] = 9;
		map[8] = 2;
		put_map(map);



1234
1243
1324
1342
1423
1432
2134
2143
2314
2341
2413
2431
3124
3142
3214
3241
3412
3421
4123
4132
4213
4231
4312
4321

4 1234 1
3 1243 2
3 1324 1
3 1342 2
2 1423 2
2 1432 3
3 2134 1
2 2143 2
3 2314 1
3 2341 2
2 2413 2
2 2431 3
2 3124 1
2 3142 2
2 3214 1
2 3241 2
2 3412 2
2 3421 3
1 4123 2
1 4132 3
1 4213 2
1 4231 3
1 4312 3
1 4321 4


0 0 0 7 
0 0 9 0 
0 0 0 0 
2 0 0 0

0 0 0 2 
0 0 0 0 
0 9 0 0 
7 0 0 0


*/