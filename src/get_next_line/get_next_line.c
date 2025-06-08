/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:01:10 by saderdou          #+#    #+#             */
/*   Updated: 2025/02/08 13:45:59 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_next_line(int fd, char *save_line)
{
	char	*buffer;
	ssize_t	count;

	buffer = (char *) malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	count = 1;
	while (count > 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[count] = '\0';
		save_line = ft_strjoin(save_line, buffer);
		if (ft_check(save_line))
			break ;
	}
	free(buffer);
	return (save_line);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = (char *) malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_new_line(char *str)
{
	int		i;
	int		j;
	char	*sline;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	sline = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!sline)
		return (NULL);
	i++;
	while (str[i])
		sline[j++] = str[i++];
	sline[j] = '\0';
	free(str);
	return (sline);
}

char	*get_next_line(int fd, int flag)
{
	static char	*save_line;
	char		*line;

	if (flag == 1)
		return (free(save_line), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save_line = ft_get_next_line(fd, save_line);
	if (!save_line)
		return (NULL);
	line = ft_get_line(save_line);
	save_line = ft_new_line(save_line);
	return (line);
}
