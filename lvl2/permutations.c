/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 12:00:40 by htavares          #+#    #+#             */
/*   Updated: 2026/03/18 12:32:13 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	swap(char *x, char *y)
{
	char temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void	sort_str(char *str, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (str[j] > str[j + 1])
				swap(&str[j], &str[j + 1]);
			j++;
		}
		i++;
	}
}

int	next_permutation(char *str, int size)
{
	int i;
	int j;
	int k;

	i = size - 2;
	while (i >= 0 && str[i] >= str[i + 1])
		i--;
	if (i < 0)
		return (0);
	j = size - 1;
	while (str[j] <= str[i])
		j--;
	swap(&str[i], &str[j]);
	i++;
	k = size - 1;
	while (i < k)
	{
		swap(&str[i], &str[k]);
		i++;
		k--;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int n;

	if (ac != 2)
		return (1);
	n = ft_strlen(av[1]);
	if (n == 0)
		return (0);
	sort_str(av[1], n);
	while (1)
	{
		write(1, av[1], n);
		write(1, "\n", 1);
		if (!next_permutation(av[1], n))
			break ;
	}
	return (0);
}

