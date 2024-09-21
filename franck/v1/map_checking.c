/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffavetta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:30:38 by ffavetta          #+#    #+#             */
/*   Updated: 2024/09/21 19:30:44 by ffavetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Fills in index for further checking of one row
// row key = base 5 number of the row
// method: "handmade", better replace this by an algo
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

// Checks if expected left & rgh match this row thanks to index okviews 
int	chk_row(int *row, int left, int right, int (*okviews)[2])
{
	int	key;

	if (row[0] == 0 || row[1] == 0 || row[2] == 0 || row[3] == 0)
		return (1);
	key = row[0] * 125 + row[1] * 25 + row[2] * 5 + row[3];
	if (okviews[key][0] != left || okviews[key][1] != right)
		return (0);
	return (1);
}

int	chk_map(int *map, int *maptr, int *views, int (*okviews)[2])
{
	return (chk_row(map + 0, views[8], views[12], okviews)
		&& chk_row(map + 4, views[9], views[13], okviews)
		&& chk_row(map + 8, views[10], views[14], okviews)
		&& chk_row(map + 12, views[11], views[15], okviews)
		&& chk_row(maptr + 0, views[0], views[4], okviews)
		&& chk_row(maptr + 4, views[1], views[5], okviews)
		&& chk_row(maptr + 8, views[2], views[6], okviews)
		&& chk_row(maptr + 12, views[3], views[7], okviews));
}
