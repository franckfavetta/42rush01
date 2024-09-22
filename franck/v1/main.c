/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffavetta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:29:56 by ffavetta          #+#    #+#             */
/*   Updated: 2024/09/21 19:30:05 by ffavetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	fill_ok(int (*okv)[2]);
void	init_ok(int (*okviews)[2]);
int		set_one_on_map(int *views, int (*okviews)[2], int *map, int pos);

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
		if (*(p + 1) != ' ' && i < 15)
			return (3);
		if (*p != '1' && *p != '2' && *p != '3' && *p != '4')
			return (4);
		views[i++] = *p - '0';
		p += 2;
	}
	return (0);
}

//Skycrapers puzzle - Piscine42-2024/9 - ffavetta/adecout/dvalenza
//Checks param + Create row checking index + Launch map browsing
//main() stores all data:
//  - views:	expected views from user parameters
//  - okviews:	index of correct views for any row combination
//  - map:		4x4 matrix grid
//Please read "readme.txt" for details
int	main(int argc, char **argv)
{
	int	views[16];
	int	retp;
	int	okviews[625][2];
	int	map[16];
	int	i;

	retp = param(argc, argv, views);
	if (retp == 0)
	{
		init_ok(okviews);
		fill_ok(okviews);
		i = 0;
		while (i < 16)
			map[i++] = 0;
		if (!set_one_on_map(views, okviews, map, 0))
			write(1, "Error\n", 6);
		return (5);
	}
	else
	{
		write(1, "Error\n", 6);
		return (retp);
	}
	return (0);
}
