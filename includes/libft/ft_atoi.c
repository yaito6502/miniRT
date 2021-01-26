/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 07:27:40 by yaito             #+#    #+#             */
/*   Updated: 2020/10/10 08:13:17 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define LLONG_MAXDIV 922337203685477580
#define LLONG_MAXSUR 7
#include "libft.h"

static	int		isoverflow(long long llnbr, int sign, char c)
{
	if (llnbr > LLONG_MAXDIV)
		return (1);
	sign = (sign < 0);
	if (llnbr == LLONG_MAXDIV && (c - '0') - sign > LLONG_MAXSUR)
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	long long	llnbr;
	int			sign;

	llnbr = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		llnbr = llnbr * 10 + (*str++ - '0');
		if (isoverflow(llnbr, sign, *str))
			return (-1 + (sign < 0));
	}
	return (llnbr * sign);
}
