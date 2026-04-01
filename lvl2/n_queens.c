/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:21:04 by htavares          #+#    #+#             */
/*   Updated: 2026/03/18 17:56:19 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

static void	print_solution(int *cols, int n)
{
	char	c;
	int		i;

	i = 0;
	while (i < n)
	{
		if (i > 0)
			write(1, " ", 1);
		c = cols[i] + '0';
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
}

static int	is_safe(int *cols, int row, int col)
{
	int	i;

	i = 0;
	while (i < row)
	{
		if (cols[i] == col || cols[i] - i == col - row
			|| cols[i] + i == col + row)
			return (0);
		i++;
	}
	return (1);
}

static void	solve(int *cols, int n, int row)
{
	int	col;

	if (row == n)
	{
		print_solution(cols, n);
		return ;
	}
	col = 0;
	while (col < n)
	{
		if (is_safe(cols, row, col))
		{
			cols[row] = col;
			solve(cols, n, row + 1);
		}
		col++;
	}
}

int	main(int argc, char **argv)
{
	int	n;
	int	cols[10];

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	n = atoi(argv[1]);
	if (n < 1 || n > 10)
	{
		write(1, "\n", 1);
		return (0);
	}
	solve(cols, n, 0);
	return (0);
}
