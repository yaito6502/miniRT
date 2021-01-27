/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 02:33:58 by yaito             #+#    #+#             */
/*   Updated: 2021/01/27 05:19:15 by yaito            ###   ########.fr       */
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
	SAFE_FREE(*line);
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
	while ((rdbyte = read(fd, buf, BUFFER_SIZE)) > END)
	{
		buf[rdbyte] = '\0';
		if (*line)
		{
			dst = ft_strjoin(*line, buf);
			SAFE_FREE(*line);
			if ((*line = dst) == NULL)
				return (ERROR);
		}
		if (!*line)
			if ((*line = ft_strdup(buf)) == NULL)
				return (ERROR);
		if (ft_strchr(*line, '\n'))
			break ;
	}
	SAFE_FREE(buf);
	return (rdbyte);
}

int		get_next_line(int fd, char **line)
{
	int			result;
	static bool	reset_s_buf = false;
	static char *s_buf[MAX_FD];

	if (!line || fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (ERROR);
	if (read(fd, s_buf[fd], 0) < 0)
		return (ERROR);
	if (reset_s_buf)
	{
		SAFE_FREE(s_buf[fd]);
		reset_s_buf = false;
	}
	result = READ;
	*line = s_buf[fd];
	if (!*line || !ft_strchr(*line, '\n'))
	{
		if ((result = readline(fd, line)) <= ERROR)
		{
			SAFE_FREE(*line);
			return (ERROR);
		}
		if (!*line)
			if (!(*line = ft_strdup("")))
				return (ERROR);
	}
	result = buf_split((result > 0), line, &s_buf[fd]);
	if (result == END)
		reset_s_buf = true;
	return (result);
}
