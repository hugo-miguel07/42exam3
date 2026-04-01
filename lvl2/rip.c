/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:35:12 by htavares          #+#    #+#             */
/*   Updated: 2026/04/01 17:36:56 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static void	write_solution(char *out, int len)
{
	write(1, out, len);
	write(1, "\n", 1);
}

static void	compute_min_removals(char *s, int *left_rem, int *right_rem)
{
	int	i;

	*left_rem = 0;
	*right_rem = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '(')
			(*left_rem)++;
		else if (s[i] == ')')
		{
			if (*left_rem > 0)
				(*left_rem)--;
			else
				(*right_rem)++;
		}
		i++;
	}
}

static void	dfs(char *in, char *out, int i, int len, int bal, int left_rem,
				int right_rem)
{
	if (i == len)
	{
		if (bal == 0 && left_rem == 0 && right_rem == 0)
			write_solution(out, len);
		return ;
	}
	if (in[i] == '(')
	{
		if (left_rem > 0)
		{
			out[i] = ' ';
			dfs(in, out, i + 1, len, bal, left_rem - 1, right_rem);
		}
		out[i] = '(';
		dfs(in, out, i + 1, len, bal + 1, left_rem, right_rem);
	}
	else
	{
		if (right_rem > 0)
		{
			out[i] = ' ';
			dfs(in, out, i + 1, len, bal, left_rem, right_rem - 1);
		}
		if (bal > 0)
		{
			out[i] = ')';
			dfs(in, out, i + 1, len, bal - 1, left_rem, right_rem);
		}
	}
}

int	main(int ac, char **av)
{
	int	len;
	int	left_rem;
	int	right_rem;

	if (ac != 2)
		return (1);
	len = ft_strlen(av[1]);
	char	out[len + 1];
	compute_min_removals(av[1], &left_rem, &right_rem);
	dfs(av[1], out, 0, len, 0, left_rem, right_rem);
	return (0);
}

