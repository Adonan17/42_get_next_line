/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouassar <aouassar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:53:57 by aouassar          #+#    #+#             */
/*   Updated: 2025/12/13 13:53:46 by aouassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_stash(int fd, char *stash);
static char	*extract_line(char *stash);
static char	*clean_stash(char *stash);
static char	*free_and_null(char **stash, char *buffer);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}

static char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_and_null(&stash, buffer));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (free_and_null(&stash, buffer));
	}
	free(buffer);
	return (stash);
}

static char	*free_and_null(char **stash, char *buffer)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	free(buffer);
	return (NULL);
}

static char	*extract_line(char *stash)
{
	char		*line;
	size_t		length;
	size_t		i;

	if (!stash || stash[0] == '\0')
		return (NULL);
	length = 0;
	i = 0;
	while (stash[length] != '\n' && stash[length])
		length++;
	if (stash[length] == '\n')
		length++;
	line = (char *)malloc(length + 1);
	if (!line)
		return (NULL);
	while (i < length)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	size_t	i;
	size_t	len;
	char	*leftovers;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	len = ft_strlen(stash + i);
	if (len == 0)
	{
		free(stash);
		return (NULL);
	}
	leftovers = ft_substr(stash, i, len);
	free(stash);
	return (leftovers);
}
