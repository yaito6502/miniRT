/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 04:07:45 by yaito             #+#    #+#             */
/*   Updated: 2021/02/06 05:31:41 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

bool	isrange(double value, double min, double max)
{
	return ((value >= min) && (value <= max));
}

double	min(double a, double b)
{
	return ((a > b) ? b : a);
}

double	max(double a, double b)
{
	return ((a > b) ? a : b);
}

bool	endswith(char *str, char *end)
{
	return (!ft_strncmp(str + (\
		ft_strlen(str) - ft_strlen(end)), end, ft_strlen(end) + 1));
}

void	safe_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
