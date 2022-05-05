/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgioia <dgioia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:30:57 by dgioia            #+#    #+#             */
/*   Updated: 2022/05/05 17:30:57 by dgioia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*ft_get_line(char *save)
{
	int		i;
	char	*s_temp;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	s_temp = (char *)malloc(sizeof(char) * (i + 2));
	if (!s_temp)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		s_temp[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		s_temp[i] = save[i];
		i++;
	}
	s_temp[i] = '\0';
	return (s_temp);
}

char	*ft_new_save(char *save)
{
	int		i;
	int		c;
	char	*s_temp;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s_temp = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!s_temp)
		return (NULL);
	i++;
	c = 0;
	while (save[i])
		s_temp[c++] = save[i++];
	s_temp[c] = '\0';
	free(save);
	return (s_temp);
}

char	*ft_read_save_str(int fd, char *save)
{
	char	*buffer;
	int		r_bytes;

	buffer = (char *) malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	r_bytes = 1;
	while (!ft_strchr(save, '\n') && r_bytes != 0)
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (r_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[r_bytes] = '\0';
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = ft_read_save_str(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_new_save(save);
	return (line);
}

/* i test vengono effettuati su tests/1.txt */
// int main(void)
// {
//  	char *line;
//  	int i;
//  	int fd;

//  	fd = open("tests/1.txt", O_RDONLY);
// 	i = 1;
//  	while (i < 7)
//  	{
//  		line = get_next_line(fd);
//  		printf("Line: %s", line);
//  		free(line);
//  		i++;
//  	}
//  	close(fd);
// 	return (0);
// }
