/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:45:19 by htavares          #+#    #+#             */
/*   Updated: 2026/04/01 17:49:24 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static int	read_all_stdin(char **buf, size_t *len)
{
	char	chunk[4096];
	char	*tmp;
	ssize_t	r;
	size_t	cap;

	*len = 0;
	cap = 4096;
	*buf = malloc(cap);
	if (!*buf)
		return (errno = ENOMEM, perror("Error"), 1);
	r = read(0, chunk, sizeof(chunk));
	while (r > 0)
	{
		if (*len + (size_t)r > cap)
		{
			while (*len + (size_t)r > cap)
				cap *= 2;
			tmp = realloc(*buf, cap);
			if (!tmp)
				return (free(*buf), errno = ENOMEM, perror("Error"), 1);
			*buf = tmp;
		}
		memmove(*buf + *len, chunk, (size_t)r);
		*len += (size_t)r;
		r = read(0, chunk, sizeof(chunk));
	}
	if (r < 0)
		return (free(*buf), perror("Error"), 1);
	return (0);
}

static int	write_filtered(char *buf, size_t len, char *needle, size_t nlen)
{
	char	*pos;
	char	*cur;
	size_t	remaining;
	char	stars[nlen];

	memset(stars, '*', nlen);
	cur = buf;
	while ((size_t)(cur - buf) < len)
	{
		remaining = len - (size_t)(cur - buf);
		pos = memmem(cur, remaining, needle, nlen);
		if (!pos)
		{
			if (write(1, cur, remaining) < 0)
				return (1);
			break ;
		}
		if (write(1, cur, (size_t)(pos - cur)) < 0)
			return (1);
		if (write(1, stars, nlen) < 0)
			return (1);
		cur = pos + nlen;
	}
	return (0);
}

int	main(int ac, char **av)
{
	char		*buf;
	char		*needle;
	size_t		nlen;
	size_t		len;

	if (ac != 2 || av[1][0] == '\0')
		return (1);
	needle = av[1];
	nlen = strlen(needle);
	if (read_all_stdin(&buf, &len))
		return (1);
	if (write_filtered(buf, len, needle, nlen))
		return (free(buf), perror("Error"), 1);
	free(buf);
	return (0);
}

