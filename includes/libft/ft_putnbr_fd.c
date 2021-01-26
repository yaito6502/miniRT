/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 06:55:40 by yaito             #+#    #+#             */
/*   Updated: 2020/10/10 06:51:47 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	put_recursive(long long int n, int fd, char c)
{
	if (n / 10 != 0)
		put_recursive(n / 10, fd, c);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void			ft_putnbr_fd(int n, int fd)
{
	long long int	lln;
	char			c;

	c = '0';
	lln = n;
	if (lln < 0)
	{
		write(fd, "-", 1);
		lln = -lln;
	}
	put_recursive(lln, fd, c);
}
