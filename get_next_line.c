/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elukutin <elukutin@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:38:04 by elukutin          #+#    #+#             */
/*   Updated: 2022/12/09 21:13:15 by elukutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static int	buf_check(char **line, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		b;

	while (!str_check(*line, '\n'))
	{
		b = read(fd, buf, BUFFER_SIZE);
		if (b == -1)
		{
			free(*line);
			*line = NULL;
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
	static char	*line;

	if (!line)
		line = ft_strdup("", 0, 0);
	if (!buf_check(&line, fd))
		return (NULL);
	if (!str_check(line, '\n'))
	{
		if (ft_strlen(line) > 0)
		{
			ret = line;
			line = NULL;
			return (ret);
		}
		free(line);
		line = NULL;
		return (NULL);
	}
	newline = ft_strchr(line, '\n');
	ret = ft_substr(line, 0, ft_strlen(line) - ft_strlen(newline) + 1);
	line = ft_strdup(newline + 1, line, 1);
	return (ret);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (search(fd));
}

#include <stdio.h>
#include <fcntl.h>
int main()
{
	char *res;
	int fd = open("get_next_line.c", O_RDONLY);
	res = get_next_line(fd);
	while (res)
	{
		printf("%s",res);
		res = get_next_line(fd);
	}
}