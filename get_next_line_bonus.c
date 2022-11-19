/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orakib <orakib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:29:36 by orakib            #+#    #+#             */
/*   Updated: 2022/11/19 16:03:08 by orakib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*readtoleft(char *leftover, int fd)
{
	char	*inbuf;
	int		rbytes;

	inbuf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!inbuf)
		return (NULL);
	rbytes = 1;
	while (rbytes != 0 && !ft_strchr(leftover))
	{
		rbytes = read(fd, inbuf, BUFFER_SIZE);
		if (rbytes == -1)
		{
			free(inbuf);
			free (leftover);
			return (NULL);
		}
		inbuf[rbytes] = '\0';
		leftover = ft_strjoin(leftover, inbuf);
	}
	free(inbuf);
	return (leftover);
}

char	*get_1line(char *leftover)
{
	int		i;
	char	*temp;

	i = 0;
	if (!leftover[i])
		return (NULL);
	while (leftover[i] && leftover[i] != '\n')
		i++;
	temp = (char *)malloc((i + 2) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (leftover[i] && leftover[i] != '\n')
	{
		temp[i] = leftover[i];
		i++;
	}
	if (leftover[i] == '\n')
	{
		temp[i] = leftover[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*fix_left(char *leftover)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (!leftover[i])
	{
		free(leftover);
		return (NULL);
	}
	temp = (char *)malloc((ft_strlen(leftover) - i + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i++;
	while (leftover[i])
		temp[j++] = leftover[i++];
	temp[j] = '\0';
	free(leftover);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*leftover[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover[fd] = readtoleft(leftover[fd], fd);
	if (!leftover[fd])
		return (NULL);
	line = get_1line(leftover[fd]);
	leftover[fd] = fix_left(leftover[fd]);
	return (line);
}
