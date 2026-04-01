/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:59:40 by htavares          #+#    #+#             */
/*   Updated: 2026/04/01 16:58:13 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static void	print_subset(int *subset, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i > 0)
			printf(" ");
		printf("%d", subset[i]);
		i++;
	}
	printf("\n");
}

static void	find_subsets(int *set, int size, int target, int index, int sum,
					int *subset, int subset_size)
{
	if (index == size)
	{
		if (sum == target)
			print_subset(subset, subset_size);
		return ;
	}
	find_subsets(set, size, target, index + 1, sum, subset, subset_size);
	subset[subset_size] = set[index];
	find_subsets(set, size, target, index + 1, sum + set[index],
		subset, subset_size + 1);
}

int	main(int ac, char **av)
{
	int	target;
	int	size;
	int	*set;
	int	*subset;
	int	i;

	if (ac < 2)
		return (1);
	target = atoi(av[1]);
	size = ac - 2;
	set = malloc(sizeof(int) * size);
	subset = malloc(sizeof(int) * size);
	if ((size > 0) && (!set || !subset))
		return (free(set), free(subset), 1);
	i = 0;
	while (i < size)
	{
		set[i] = atoi(av[i + 2]);
		i++;
	}
	find_subsets(set, size, target, 0, 0, subset, 0);
	free(set);
	free(subset);
	return (0);
}
