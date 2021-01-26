/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 04:05:28 by yaito             #+#    #+#             */
/*   Updated: 2021/01/20 19:46:35 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef MAX_FD
#  define MAX_FD 256
# endif
# define READ 1
# define END 0
# define ERROR -1
# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
int		readline(int fd, char **line);
int		buf_split(int rval, char **line, char **buf);

#endif
