/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elukutin <elukutin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:38:04 by elukutin          #+#    #+#             */
/*   Updated: 2022/11/15 13:19:46 by elukutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	str_check(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	*delete(char **line)
{
	free(*line);
	*line = NULL;
	return (NULL);
}

static int	buf_check(char **line, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		b;

	while (!str_check(*line, '\n'))
	{
		b = read(fd, buf, BUFFER_SIZE);
		if (b == -1)
		{
			delete (line);
			return (0);
		}
		buf[b] = '\0';
		if (b == 0)
			break ;
		*line = ft_strjoin(*line, buf);
	}
	return (1);
}

static char	*search(int fd)
{
	char		*ret;
	char		*newline;
	static char	*line[1024];

	if (!line[fd])
		line[fd] = ft_strdup("");
	if (!buf_check(&line[fd], fd))
		return (NULL);
	if (!str_check(line[fd], '\n'))
	{
		if (ft_strlen(line[fd]) > 0)
		{
			ret = line[fd];
			line[fd] = NULL;
			return (ret);
		}
		return (delete (&line[fd]));
	}
	newline = ft_strchr(line[fd], '\n');
	ret = ft_substr(line[fd], 0, ft_strlen(line[fd]) - ft_strlen(newline));
	free(line[fd]);
	line[fd] = ft_strdup(newline + 1);
	return (ret);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (search(fd));
}
