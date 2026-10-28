/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhashan <hkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 15:05:37 by hkhashan          #+#    #+#             */
/*   Updated: 2026/10/28 16:23:07 by hkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*extract_line(char *leftover)
{
	int		i;
	char	*str;

	i = 0;
	if (!leftover[i])
		return (NULL);
	while (leftover[i] && leftover[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (leftover[i] && leftover[i] != '\n')
	{
		str[i] = leftover[i];
		i++;
	}
	if (leftover[i] == '\n')
	{
		str[i] = leftover[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*update_leftover(char *leftover)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (!leftover[i])
	{
		free(leftover);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(leftover) - i + 1));
	if (!str)
	{
		free(leftover);
		return (NULL);
	}
	i++;
	j = 0;
	while (leftover[i])
		str[j++] = leftover[i++];
	str[j] = '\0';
	free(leftover);
	return (str);
}

char	*read_to_leftover(int fd, char *leftover)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(leftover, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(leftover);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
	}
	free(buffer);
	return (leftover);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = read_to_leftover(fd, leftover);
	if (!leftover)
		return (NULL);
	line = extract_line(leftover);
	leftover = update_leftover(leftover);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*line1;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("error opining file\n");
		return (1);
	}
	line1 = get_next_line(fd);
	printf("%s", line1);
	line1 = get_next_line(fd);
	printf("%s", line1);
	line1 = get_next_line(fd);
	printf("%s", line1);
	line1 = get_next_line(fd);
	printf("%s", line1);
	close(fd);
	return (0);
}
*/