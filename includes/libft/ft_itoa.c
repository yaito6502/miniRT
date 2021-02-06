/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 20:48:01 by yaito             #+#    #+#             */
/*   Updated: 2020/10/10 04:24:10 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		culclen(int n)
{
	int c;

	c = 1;
	while (n /= 10)
		c++;
	return (c);
}

char			*ft_itoa(int n)
{
	long int	ln;
	int			sign;
	int			len;
	char		*str;

	ln = n;
	sign = 0;
	if (n < 0)
	{
		ln = -ln;
		sign = 1;
	}
	len = culclen(ln);
	if ((str = malloc(sign + len + 1)) == NULL)
		return (NULL);
	*str = '-';
	str[sign + len] = '\0';
	while (len)
	{
		str[sign + len - 1] = ln % 10 + '0';
		ln /= 10;
		len--;
	}
	return (str);
}
