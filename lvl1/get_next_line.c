/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:06:58 by htavares          #+#    #+#             */
/*   Updated: 2026/03/18 18:06:59 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;
	char	*join;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	join = malloc(s1len + s2len + 1);
	if (!join)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (i < s1len)
	{
		join[i] = s1[i];
		i++;
	}
	while (j < s2len)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (free(s1), join);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == 0)
		return ((char *)str);
	return (NULL);
}

void	move_buff(char *buffer)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(buffer);
	while (buffer[i])
		buffer[j++] = buffer[i++];
	while (j < BUFFER_SIZE)
		buffer[j++] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (!ft_strchr(line, '\n'))
	{
		if (buffer[0] == '\0')
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read < 0)
				return (free(line), NULL);
			if (bytes_read == 0)
				break ;
		}
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
		move_buff(buffer);
	}
	return (line);
}

/* int main(void)
{
	int fd = open ("test.txt", O_RDONLY);
	char *str;

	while((str = get_next_line(fd)) != NULL)
	{
		printf("%s",str);
		free(str);
	}
	close(fd);
	return (0);
} */