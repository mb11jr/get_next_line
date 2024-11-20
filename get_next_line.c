/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:17:39 by mbentale          #+#    #+#             */
/*   Updated: 2024/11/20 10:56:18 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*add_to_stash(char *stash_buffer, char *read_buffer)
{
	char	*result;

	result = ft_strjoin(stash_buffer, read_buffer);
	free(stash_buffer);
	return (result);
}

static char	*read_from_file(char *stash_buffer, int fd)
{
	char	*read_buffer;
	int		bytes_read;

	read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		read_buffer[bytes_read] = '\0';
		stash_buffer = add_to_stash(stash_buffer, read_buffer);
		if (ft_strchr(stash_buffer, '\n'))
			break ;
	}
	// if (bytes_read == -1)
	// {
	// 	free(read_buffer);
	// 	free(stash_buffer);
	// 	return (NULL);
	// }
	free(read_buffer);
	return (stash_buffer);
}

// static char	*extract_line(char *buffer)
// {
// 	char	*sub_line;
// 	int		i;

// 	i = 0;
// 	while (buffer[i] && buffer[i] != '\n')
// 		i++;
//     if (buffer[i] == '\n')
//         i++;
// 	sub_line = ft_substr(buffer, 0, i);
// 	return (sub_line);
// }

// static char	*get_rest_of(char *stash_buffer)
// {
// 	char	*rest;
// 	int		i;

// 	i = 0;
// 	while (stash_buffer[i] && stash_buffer[i] != '\n')
//         i++;
// 	if (stash_buffer[i] == '\n')
//         i++;
// 	rest = ft_substr(stash_buffer, i, ft_strlen(stash_buffer) - i);
//     free(stash_buffer);
// 	return (rest);
// }

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash_buffer;
	int			i;
	char		*rest;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// if (!stash_buffer)
	//     stash_buffer = ft_strdup("");
	// if (!ft_strchr(stash_buffer, '\n'))
	stash_buffer = read_from_file(stash_buffer, fd);
	if (!stash_buffer || !*stash_buffer)
	{
		free(stash_buffer);
		stash_buffer = NULL;
		return (NULL);
	}
	i = 0;
	while (stash_buffer[i] && stash_buffer[i] != '\n')
		i++;
	if (stash_buffer[i] == '\n')
		i++;
	line = ft_substr(stash_buffer, 0, i);
	rest = ft_substr(stash_buffer, i, ft_strlen(stash_buffer) - i);
	free(stash_buffer);
	stash_buffer = rest;
	// line = extract_line(stash_buffer);
	// stash_buffer = get_rest_of(stash_buffer);
	return (line);
}
