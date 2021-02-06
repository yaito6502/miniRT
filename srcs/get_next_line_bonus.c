/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 02:33:58 by yaito             #+#    #+#             */
/*   Updated: 2021/02/06 04:21:00 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		buf_split(int rval, char **line, char **buf)
{
	char *newlinep;
	char *store;

	store = NULL;
	if ((newlinep = ft_strchr(*line, '\n')) == NULL)
		return (rval);
	if ((*buf = ft_strdup(newlinep + 1)) == NULL)
		rval = ERROR;
	else if ((store = ft_substr(*line, 0, newlinep - *line)) == NULL)
		rval = ERROR;
	safe_free(*line);
	*line = store;
	return (rval);
}

int		readline(int fd, char **line)
{
	int		rdbyte;
	char	*buf;
	char	*dst;

	if ((buf = malloc(BUFFER_SIZE + 1)) == NULL)
		return (ERROR);
	while ((rdbyte = read(fd, buf, BUFFER_SIZE)) >= READ)
	{
		buf[rdbyte] = '\0';
		if (*line)
		{
			dst = ft_strjoin(*line, buf);
			safe_free(*line);
			if ((*line = dst) == NULL)
				return (ERROR);
		}
		if (!*line)
			if ((*line = ft_strdup(buf)) == NULL)
				return (ERROR);
		if (ft_strchr(*line, '\n'))
			break ;
	}
	safe_free(buf);
	return (rdbyte);
}

int		get_next_line(int fd, char **line)
{
	int			result;
	static char *s_buf[MAX_FD];

	if (!line || fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (ERROR);
	if (read(fd, s_buf[fd], 0) < 0)
		return (ERROR);
	result = READ;
	*line = s_buf[fd];
	s_buf[fd] = NULL;
	if (!*line || !ft_strchr(*line, '\n'))
	{
		if ((result = readline(fd, line)) == ERROR)
		{
			safe_free(*line);
			return (ERROR);
		}
		if (!*line)
			if (!(*line = ft_strdup("")))
				return (ERROR);
	}
	result = buf_split((result > 0), line, &s_buf[fd]);
	return (result);
}
