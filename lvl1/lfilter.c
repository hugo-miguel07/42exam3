/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfilter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:07:12 by htavares          #+#    #+#             */
/*   Updated: 2026/03/18 18:09:32 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

static size_t	ft_strlen_all(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static int	contains(const char *line, const char *pattern)
{
	size_t	i;
	size_t	j;

	if (!pattern[0])
		return (1);
	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i + j] && pattern[j] && line[i + j] == pattern[j])
			j++;
		if (!pattern[j])
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	*line;

	if (argc != 2)
		return (1);
	line = get_next_line(0);
	while (line)
	{
		if (contains(line, argv[1]))
			write(1, line, ft_strlen_all(line));
		free(line);
		line = get_next_line(0);
	}
	return (0);
}

